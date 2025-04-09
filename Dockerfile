FROM ubuntu:latest
LABEL authors="the_snake_team"

# Install CMake and build tools
RUN apt-get update && \
    apt-get install -y \
        cmake \
        build-essential \
        git \
    && rm -rf /var/lib/apt/lists/* \

CMD ["/bin/bash"]

WORKDIR /usr/src/app

COPY . ./snake

RUN cd snake && \
    cmake . && \
    make
