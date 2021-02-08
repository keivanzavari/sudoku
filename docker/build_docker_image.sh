#!/usr/bin/env bash

docker build -t tesseract-opencv . --build-arg user_name=$LOGNAME
