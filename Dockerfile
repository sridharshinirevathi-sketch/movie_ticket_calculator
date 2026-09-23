FROM gcc:14

WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

COPY movie_ticket.cpp .

RUN g++ -std=c++17 movie_ticket.cpp -lsqlite3 -o movie_ticket

CMD ["./movie_ticket"]
