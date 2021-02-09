#!/usr/bin/env bash

IMAGE="tesseract-opencv"
CONTAINER_NAME="tesseract-opncv-env"
function create_container_prompt() {

  read -p "Container already running (${CONTAINER_NAME}). Reuse running container? (Y/n)? " -r
  echo # (optional) move to a new line

  if [[ $REPLY =~ ^[Nn]$ ]]; then
    return 0
  else
    return 1
  fi
}

if [[ ! $(docker ps -f "name=${CONTAINER_NAME}" --format '{{.Names}}') == ${CONTAINER_NAME} ]] || create_container_prompt; then
  docker rm -f ${CONTAINER_NAME} &>/dev/null | true

  docker run -dti --init --privileged --net host --name ${CONTAINER_NAME} \
    --mount type=bind,source=/home/keivan/playground/sudoku,target=/home/${LOGNAME}/sudoku \
    --volume /home/${LOGNAME}/.Xauthority:/home/${LOGNAME}/.Xauthority \
    --volume /home/${LOGNAME}/.ssh:/home/${LOGNAME}/.ssh \
    --volume /tmp/.X11-unix:/tmp/.X11-unix \
    --volume /var/run/docker.sock:/var/run/docker.sock \
    --volume /var/run/sshd:/var/run/sshd \
    -e DISPLAY \
    -e TESSDATA_PREFIX=/home \
    ${IMAGE}
else
  echo "Reusing docker container ${CONTAINER_NAME}."
  docker start ${CONTAINER_NAME}
fi

sleep 0.1
docker exec -it ${CONTAINER_NAME} /bin/bash
