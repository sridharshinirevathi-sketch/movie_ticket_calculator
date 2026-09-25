FROM python:3.12-slim

WORKDIR /app

COPY Movie_Ticket_Website/requirements.txt ./requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY Movie_Ticket_Website/ ./Movie_Ticket_Website/

WORKDIR /app/Movie_Ticket_Website

CMD ["python", "app.py"]
