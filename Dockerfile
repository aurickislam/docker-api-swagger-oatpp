FROM debian:bookworm-slim

RUN apt update && apt upgrade -y && apt install -y git cmake build-essential gdb libcurl4-openssl-dev pkg-config \
    && rm -rf /var/lib/apt/lists/*

ARG MAKE_PARALLEL_EXECUTION
ENV MAKE_PARALLEL_EXECUTION $MAKE_PARALLEL_EXECUTION

COPY ./utility/install-oatpp-modules-dev.sh /

WORKDIR /

RUN bash install-oatpp-modules-dev.sh Release

WORKDIR /app
