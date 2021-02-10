FROM ubuntu:20.04

USER root
WORKDIR /

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt-get update && apt-get install -y build-essential xauth x11-apps sudo \
    wget g++ make cmake vim tmux git libgtk2.0-dev pkg-config \
    libavcodec-dev libavformat-dev libswscale-dev \
    python3-dev python3-pip python3-numpy libtbb2 \
    libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev \
    && apt-get clean && rm -rf /var/lib/apt-lists/*

RUN apt-get install  -y --no-install-recommends libopenblas-dev liblapack-dev

ARG OPENCV_VERSION=4.5.1
RUN wget -q -O opencv-${OPENCV_VERSION}.tar.gz https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.tar.gz && \
    wget -q -O opencv_contrib-${OPENCV_VERSION}.tar.gz https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.tar.gz && \
    tar -xvf opencv-${OPENCV_VERSION}.tar.gz && \
    tar -xvf opencv_contrib-${OPENCV_VERSION}.tar.gz &&\
    cd /opencv-${OPENCV_VERSION} && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-${OPENCV_VERSION}/modules \
      -DBUILD_EXAMPLES=OFF -DINSTALL_TESTS=OFF -DBUILD_opencv_python2=OFF \
      -DBUILD_opencv_python3=ON -DPYTHON3_EXECUTABLE=/usr/bin/python3 \
      -DENABLE_PRECOMPILED_HEADERS=OFF .. -DOPENCV_GENERATE_PKGCONFIG=ON && \
    make && \
    make install && \
    cd / && \
    rm  -rf opencv-${OPENCV_VERSION}.tar.gz opencv_contrib-${OPENCV_VERSION}.tar.gz opencv-${OPENCV_VERSION} opencv_contrib-${OPENCV_VERSION}


RUN apt-get install -y automake ca-certificates libtool autoconf zlib1g-dev libleptonica-dev libtesseract-dev
RUN cd /home && wget -q https://github.com/tesseract-ocr/tessdata/raw/master/eng.traineddata

ARG user_name
ENV USER=${user_name}
RUN adduser ${user_name} && \
    usermod -aG sudo,video,dialout ${user_name} && \
    mkdir -p /etc/sudoers.d && \
    echo "${user_name} ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/${user_name} && \
    chmod 0440 /etc/sudoers.d/${user_name}

COPY entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh
ENTRYPOINT ["/bin/bash","/usr/local/bin/entrypoint.sh"]

USER ${user_name}
ENV USER=${user_name}
WORKDIR /home/${user_name}

CMD ["/bin/bash"]
