# Stage 1: Build
FROM ubuntu:latest AS builder

LABEL authors="the_snake_team"

RUN apt-get update && \
    apt-get install -y \
        cmake \
        build-essential \
        git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY . .

RUN cmake . && \
    make

# Stage 2: Runtime
FROM ubuntu:latest

LABEL authors="the_snake_team"

WORKDIR /usr/src/app

COPY --from=builder /build/snake .

RUN mkdir -p /usr/src/app/files

CMD ["./snake"]
