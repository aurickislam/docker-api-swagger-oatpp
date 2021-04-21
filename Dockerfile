FROM alpine:latest

RUN apk update && apk upgrade && apk add g++ git make cmake pkgconfig curl-dev

COPY ./utility /app/utility

WORKDIR /app/utility

RUN sh install-oatpp-modules.sh Release

COPY ./ /app/

WORKDIR /app/build

RUN cmake ..
RUN make -j $(nproc)

# EXPOSE 8000

ENTRYPOINT ["./docker-api-swagger"]
