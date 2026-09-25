import csv
import io
import json
import os
from http import HTTPStatus
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import sqlite3

from openpyxl import Workbook
from openpyxl.styles import Font


BASE_DIR = Path(__file__).resolve().parent
DATABASE_PATH = BASE_DIR / "movie_ticket.db"
WORKBOOK_PATH = BASE_DIR / "booking.xlsx"


def initialize_database():
    """Create the SQLite database file and bookings table if needed."""
    with sqlite3.connect(DATABASE_PATH) as db:
        db.execute("""
            CREATE TABLE IF NOT EXISTS bookings (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL,
                email_id TEXT NOT NULL,
                movie_name TEXT NOT NULL,
                show_time TEXT NOT NULL,
                adult_tickets INTEGER NOT NULL,
                child_tickets INTEGER NOT NULL,
                ticket_amount REAL NOT NULL,
                snack_name TEXT NOT NULL,
                snack_amount REAL NOT NULL,
                subtotal REAL NOT NULL,
                discount REAL NOT NULL,
                gst REAL NOT NULL,
                total_amount REAL NOT NULL,
                created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
            )
        """)


def create_booking_workbook():
    """Create a real Excel workbook from every booking in the SQLite database."""
    with sqlite3.connect(DATABASE_PATH) as db:
        cursor = db.execute("SELECT * FROM bookings ORDER BY id DESC")
        headers = [column[0] for column in cursor.description]
        rows = cursor.fetchall()

    workbook = Workbook()
    worksheet = workbook.active
    worksheet.title = "Bookings"
    worksheet.append(headers)
    for row in rows:
        worksheet.append(row)

    for cell in worksheet[1]:
        cell.font = Font(bold=True)
    worksheet.freeze_panes = "A2"
    worksheet.auto_filter.ref = worksheet.dimensions
    for column in worksheet.columns:
        letter = column[0].column_letter
        worksheet.column_dimensions[letter].width = min(
            max(len(str(cell.value or "")) for cell in column) + 2, 30
        )

    workbook.save(WORKBOOK_PATH)


class BookingRequestHandler(SimpleHTTPRequestHandler):
    """Serve the website files and accept booking requests."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(BASE_DIR), **kwargs)

    def do_GET(self):
        """Download all saved bookings as an Excel-compatible CSV file."""
        if self.path == "/export-bookings":
            self.export_bookings()
            return
        super().do_GET()

    def do_POST(self):
        if self.path != "/book":
            self.send_error(HTTPStatus.NOT_FOUND, "Endpoint not found")
            return

        try:
            content_length = int(self.headers.get("Content-Length", 0))
            data = json.loads(self.rfile.read(content_length).decode("utf-8"))
            booking_id = self.save_booking(data)
            self.send_json(HTTPStatus.OK, {
                "success": True,
                "message": "Booking saved successfully!",
                "booking_id": booking_id,
            })
        except (KeyError, TypeError, ValueError, json.JSONDecodeError) as error:
            self.send_json(HTTPStatus.BAD_REQUEST, {
                "success": False,
                "message": f"Invalid booking data: {error}",
            })
        except sqlite3.Error:
            self.log_error("Could not save booking")
            self.send_json(HTTPStatus.INTERNAL_SERVER_ERROR, {
                "success": False,
                "message": "Could not save the booking.",
            })

    @staticmethod
    def save_booking(data):
        values = (
            str(data["username"]).strip(), str(data["email_id"]).strip(),
            str(data["movie_name"]).strip(), str(data["show_time"]).strip(),
            int(data["adults"]), int(data["children"]), float(data["ticket_amount"]),
            str(data["snack_name"]).strip(), float(data["snack_amount"]),
            float(data["subtotal"]), float(data["discount"]), float(data["gst"]),
            float(data["total_amount"]),
        )
        if not all(values[:4]) or values[4] < 0 or values[5] < 0:
            raise ValueError("Please enter valid booking details.")

        with sqlite3.connect(DATABASE_PATH) as db:
            cursor = db.execute("""
                INSERT INTO bookings (
                    username, email_id, movie_name, show_time, adult_tickets,
                    child_tickets, ticket_amount, snack_name, snack_amount,
                    subtotal, discount, gst, total_amount
                ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
            """, values)
            booking_id = cursor.lastrowid

        create_booking_workbook()
        return booking_id

    def send_json(self, status, data):
        body = json.dumps(data).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def export_bookings(self):
        with sqlite3.connect(DATABASE_PATH) as db:
            cursor = db.execute("SELECT * FROM bookings ORDER BY id DESC")
            headers = [column[0] for column in cursor.description]
            rows = cursor.fetchall()

        output = io.StringIO(newline="")
        writer = csv.writer(output)
        writer.writerow(headers)
        writer.writerows(rows)
        create_booking_workbook()
        body = WORKBOOK_PATH.read_bytes()

        self.send_response(HTTPStatus.OK)
        self.send_header(
            "Content-Type",
            "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
        )
        self.send_header("Content-Disposition", "attachment; filename=booking.xlsx")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)


if __name__ == "__main__":
    initialize_database()
    create_booking_workbook()
    port = int(os.environ.get("PORT", "5001"))
    server = ThreadingHTTPServer(("0.0.0.0", port), BookingRequestHandler)
    print(f"Movie Ticket Website is running on port {port}")
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nServer stopped.")
    finally:
        server.server_close()