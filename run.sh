cd ./build

export DOCKER_SERVER_IP=192.168.88.18
export DOCKER_SERVER_PORT=2375

clear && make -j $(nproc) && ./docker-api-swagger