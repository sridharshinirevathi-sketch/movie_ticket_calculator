FROM gcc:latest

WORKDIR /app

COPY movie_ticket.cpp .

RUN g++ movie_ticket.cpp -o movie_ticket

CMD ["./movie_ticket"]