FROM alpine:latest as build

RUN apk update && apk upgrade && apk add g++ git make cmake pkgconfig curl-dev

COPY ./utility /app/utility

WORKDIR /app/utility

RUN sh install-oatpp-modules.sh Release

COPY ./ /app/

WORKDIR /app/build

RUN cmake ..
RUN make -j $(nproc)


FROM alpine:latest

RUN apk update && apk upgrade && apk add g++

COPY --from=build /app/build/docker-api-swagger /app/build/docker-api-swagger

# COPY ./res /app/res
COPY --from=build /app/res /app/res

WORKDIR /app/build

# EXPOSE 8001

CMD ["./docker-api-swagger"]
