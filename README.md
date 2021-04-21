# docker-api-swagger-oatpp
Swagger UI for Docker Engine API written in C++ based on [Oat++](https://oatpp.io/) web framework.

**Before using it you have to open `Docker Engine API` port on server where you are running docker. Follow these steps:**

1. Create a file at `/etc/systemd/system/docker.service.d/startup_options.conf` with the below contents:
    ```
    # /etc/systemd/system/docker.service.d/override.conf
    [Service]
    ExecStart=
    ExecStart=/usr/bin/dockerd -H fd:// -H tcp://0.0.0.0:2375
    ```
    >**Note:** The -H flag binds dockerd to a listening socket, either a Unix socket or a TCP port. You can specify multiple -H flags to bind to multiple sockets/ports. The default -H fd:// uses systemd's socket activation feature to refer to /lib/systemd/system/docker.socket.
1. Reload the unit files:
    ```shell script
    sudo systemctl daemon-reload
    ```
1. Restart the docker daemon with new startup options:
    ```shell script
    sudo systemctl restart docker.service
    ```
1. Ensure that anyone that has access to the TCP listening socket is a trusted user since access to the docker daemon is root-equivalent.

### Build
```shell script
mkdir build && cd build
cmake ..
make -j $(nproc)
```
### Run
```shell script
./docker-api-swagger
```
