#!/usr/bin/env bash

IMAGE="tesseract-opencv"
CONTAINER_NAME="tesseract-opncv-env"
docker rm -f ${CONTAINER_NAME} &>/dev/null | true

docker run -dti --init --privileged --net host --name ${CONTAINER_NAME} \
    	--mount type=bind,source=/home/keivan/playground/sudoku,target=/home/sudoku \
	--volume /home/${LOGNAME}/.Xauthority:/home/sv/.Xauthority \
	--volume /home/${LOGNAME}/.ssh:/home/sv/.ssh \
	--volume /tmp/.X11-unix:/tmp/.X11-unix \
	--volume /var/run/docker.sock:/var/run/docker.sock \
	--volume /var/run/sshd:/var/run/sshd \
	-e DISPLAY \
	${IMAGE}

docker exec -it ${CONTAINER_NAME} /bin/bash

