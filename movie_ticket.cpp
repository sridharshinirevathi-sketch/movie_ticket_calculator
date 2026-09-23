#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    cout << "===================================" << endl;
    cout << "      MOVIE TICKET CALCULATOR" << endl;
    cout << "===================================" << endl;

    cout << "\nAvailable Movies:" << endl;
    cout << "1. Jananayagan" << endl;
    cout << "2. Spider-Man:Brand New Day" << endl;
    cout << "3. Vishwanathan & sons" << endl;

    int movie_choice;
    cout << "Select Movie: ";
    cin >> movie_choice;

    string movie_name;

    if (movie_choice == 1)
    {
        movie_name = "Jananayagan";
    }
    else if (movie_choice == 2)
    {
        movie_name = "Spider-Man:Brand New Day";
    }
    else if (movie_choice == 3)
    {
        movie_name = "Vishwanathan & sons";
    }
    else
    {
        cout << "Invalid Movie Selection" << endl;
        return 0;
    }

    cout << "\nAvailable Show Times:" << endl;
    cout << "1. 10:00 AM" << endl;
    cout << "2. 2:00 PM" << endl;
    cout << "3. 6:00 PM" << endl;
    cout << "4. 10:00 PM" << endl;

    int show_choice;
    cout << "Select Show Time: ";
    cin >> show_choice;

    string show_time;

    if (show_choice == 1)
    {
        show_time = "10:00 AM";
    }
    else if (show_choice == 2)
    {
        show_time = "2:00 PM";
    }
    else if (show_choice == 3)
    {
        show_time = "6:00 PM";
    }
    else if (show_choice == 4)
    {
        show_time = "10:00 PM";
    }
    else
    {
        cout << "Invalid Show Time" << endl;
        return 0;
    }

    int adult_price = 200;
    int child_price = 120;

    cout << "\nTicket Price:" << endl;
    cout << "Adult : Rs.200" << endl;
    cout << "Child : Rs.120" << endl;

    int adult_tickets, child_tickets;

    cout << "\nEnter number of Adult tickets: ";
    cin >> adult_tickets;

    cout << "Enter number of Child tickets: ";
    cin >> child_tickets;

    int adult_amount = adult_tickets * adult_price;
    int child_amount = child_tickets * child_price;

    int ticket_total = adult_amount + child_amount;

    cout << "\n===== SNACKS =====" << endl;
    cout << "1. Popcorn       - Rs.150" << endl;
    cout << "2. Coke          - Rs.100" << endl;
    cout << "3. Popcorn + Coke - Rs.220" << endl;
    cout << "4. No Snacks" << endl;

    int snack_choice;
    cout << "Select Snacks: ";
    cin >> snack_choice;

    string snack_name;
    int snack_price;

    if (snack_choice == 1)
    {
        snack_name = "Popcorn";
        snack_price = 150;
    }
    else if (snack_choice == 2)
    {
        snack_name = "Coke";
        snack_price = 100;
    }
    else if (snack_choice == 3)
    {
        snack_name = "Popcorn + Coke";
        snack_price = 220;
    }
    else if (snack_choice == 4)
    {
        snack_name = "No Snacks";
        snack_price = 0;
    }
    else
    {
        cout << "Invalid Snack Selection" << endl;
        return 0;
    }

    int subtotal = ticket_total + snack_price;

    int discount;

    if (subtotal >= 1000)
    {
        discount = 100;
    }
    else if (subtotal >= 500)
    {
        discount = 50;
    }
    else
    {
        discount = 0;
    }

    double amount_after_discount = subtotal - discount;

    double gst = amount_after_discount * 0.05;

    double final_amount = amount_after_discount + gst;

    cout << "\n===================================" << endl;
    cout << "         BOOKING SUMMARY" << endl;
    cout << "===================================" << endl;

    cout << "Movie Name      : " << movie_name << endl;
    cout << "Show Time       : " << show_time << endl;

    cout << "\nAdult Tickets   : " << adult_tickets << endl;
    cout << "Child Tickets   : " << child_tickets << endl;

    cout << "Ticket Amount   : Rs." << ticket_total << endl;
    cout << "Snacks          : " << snack_name << endl;
    cout << "Snacks Amount   : Rs." << snack_price << endl;

    cout << "-----------------------------------" << endl;

    cout << "Subtotal        : Rs." << subtotal << endl;
    cout << "Discount        : Rs." << discount << endl;

    cout << fixed << setprecision(2);
    cout << "GST (5%)        : Rs." << gst << endl;

    cout << "-----------------------------------" << endl;

    cout << "Final Amount    : Rs." << final_amount << endl;

    cout << "===================================" << endl;
    cout << "       BOOKING SUCCESSFUL!" << endl;
    cout << "===================================" << endl;

    return 0;
}
#include <iomanip>
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <string>

using namespace std;

bool read_non_negative_number(const string& prompt, int& number) {
    cout << prompt;
    cin >> number;
    if (cin.fail() || number < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid non-negative number.\n";
        return false;
    }
    return true;
}

bool save_booking(const string& username, const string& email, const string& movie,
                  const string& show_time, int adults, int children, int ticket_amount,
                  const string& snack, int snack_amount, int subtotal, int discount,
                  double gst, double final_amount) {
    sqlite3* database = nullptr;
    if (sqlite3_open("movie_ticket.db", &database) != SQLITE_OK) {
        cerr << "Database open error: " << sqlite3_errmsg(database) << '\n';
        sqlite3_close(database);
        return false;
    }

    const char* create_table = R"(
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
        );
    )";

    char* error_message = nullptr;
    if (sqlite3_exec(database, create_table, nullptr, nullptr, &error_message) != SQLITE_OK) {
        cerr << "Database table error: " << error_message << '\n';
        sqlite3_free(error_message);
        sqlite3_close(database);
        return false;
    }

    const char* insert_booking = R"(
        INSERT INTO bookings (
            username, email_id, movie_name, show_time, adult_tickets, child_tickets,
            ticket_amount, snack_name, snack_amount, subtotal, discount, gst, total_amount
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(database, insert_booking, -1, &statement, nullptr) != SQLITE_OK) {
        cerr << "Database prepare error: " << sqlite3_errmsg(database) << '\n';
        sqlite3_close(database);
        return false;
    }

    sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, movie.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, show_time.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, adults);
    sqlite3_bind_int(statement, 6, children);
    sqlite3_bind_double(statement, 7, ticket_amount);
    sqlite3_bind_text(statement, 8, snack.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(statement, 9, snack_amount);
    sqlite3_bind_double(statement, 10, subtotal);
    sqlite3_bind_double(statement, 11, discount);
    sqlite3_bind_double(statement, 12, gst);
    sqlite3_bind_double(statement, 13, final_amount);

    const bool saved = sqlite3_step(statement) == SQLITE_DONE;
    if (!saved) {
        cerr << "Database save error: " << sqlite3_errmsg(database) << '\n';
    }
    sqlite3_finalize(statement);
    sqlite3_close(database);
    return saved;
}

int main() {
    cout << "===================================\n";
    cout << "      MOVIE TICKET CALCULATOR\n";
    cout << "===================================\n";

    string username, email;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter email ID: ";
    getline(cin, email);
    if (username.empty() || email.empty()) {
        cout << "Username and email ID are required.\n";
        return 1;
    }

    cout << "\nAvailable Movies:\n1. Jananayagan\n2. Spider-Man: Brand New Day\n3. Vishwanathan & Sons\n";
    int movie_choice;
    if (!read_non_negative_number("Select Movie: ", movie_choice)) return 1;
    const string movies[] = {"", "Jananayagan", "Spider-Man: Brand New Day", "Vishwanathan & Sons"};
    if (movie_choice < 1 || movie_choice > 3) {
        cout << "Invalid movie selection.\n";
        return 1;
    }
    const string movie_name = movies[movie_choice];

    cout << "\nAvailable Show Times:\n1. 10:00 AM\n2. 2:00 PM\n3. 6:00 PM\n4. 10:00 PM\n";
    int show_choice;
    if (!read_non_negative_number("Select Show Time: ", show_choice)) return 1;
    const string shows[] = {"", "10:00 AM", "2:00 PM", "6:00 PM", "10:00 PM"};
    if (show_choice < 1 || show_choice > 4) {
        cout << "Invalid show time.\n";
        return 1;
    }
    const string show_time = shows[show_choice];

    int adult_tickets, child_tickets;
    if (!read_non_negative_number("\nEnter number of adult tickets (Rs.200): ", adult_tickets) ||
        !read_non_negative_number("Enter number of child tickets (Rs.120): ", child_tickets)) return 1;
    if (adult_tickets + child_tickets == 0) {
        cout << "Please book at least one ticket.\n";
        return 1;
    }

    cout << "\n===== SNACKS =====\n1. Popcorn - Rs.150\n2. Coke - Rs.100\n3. Popcorn + Coke - Rs.220\n4. No Snacks\n";
    int snack_choice;
    if (!read_non_negative_number("Select Snacks: ", snack_choice)) return 1;
    const string snacks[] = {"", "Popcorn", "Coke", "Popcorn + Coke", "No Snacks"};
    const int snack_prices[] = {0, 150, 100, 220, 0};
    if (snack_choice < 1 || snack_choice > 4) {
        cout << "Invalid snack selection.\n";
        return 1;
    }

    const int ticket_amount = adult_tickets * 200 + child_tickets * 120;
    const string snack_name = snacks[snack_choice];
    const int snack_amount = snack_prices[snack_choice];
    const int subtotal = ticket_amount + snack_amount;
    const int discount = subtotal >= 1000 ? 100 : (subtotal >= 500 ? 50 : 0);
    const double gst = (subtotal - discount) * 0.05;
    const double final_amount = subtotal - discount + gst;

    cout << fixed << setprecision(2);
    cout << "\n===================================\nBOOKING SUMMARY\n===================================\n";
    cout << "Username         : " << username << "\nEmail ID         : " << email;
    cout << "\nMovie            : " << movie_name << "\nShow Time        : " << show_time;
    cout << "\nAdult Tickets    : " << adult_tickets << "\nChild Tickets    : " << child_tickets;
    cout << "\nTicket Amount    : Rs." << ticket_amount << "\nSnacks           : " << snack_name;
    cout << "\nSnacks Amount    : Rs." << snack_amount << "\nSubtotal         : Rs." << subtotal;
    cout << "\nDiscount         : Rs." << discount << "\nGST (5%)         : Rs." << gst;
    cout << "\n-----------------------------------\nFinal Amount     : Rs." << final_amount << "\n";

    if (save_booking(username, email, movie_name, show_time, adult_tickets, child_tickets,
                     ticket_amount, snack_name, snack_amount, subtotal, discount, gst, final_amount)) {
        cout << "===================================\nBOOKING SUCCESSFUL! Saved to movie_ticket.db\n===================================\n";
        return 0;
    }

    cout << "Booking was not saved.\n";
    return 1;
}