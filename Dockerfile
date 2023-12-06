FROM debian:bookworm-slim

RUN apt update && apt upgrade -y && apt install -y git cmake build-essential libcurl4-openssl-dev pkg-config

ARG MAKE_PARALLEL_EXECUTION
ENV MAKE_PARALLEL_EXECUTION $MAKE_PARALLEL_EXECUTION

COPY ./utility /app/utility

WORKDIR /app/utility

RUN bash install-oatpp-modules.sh Release
