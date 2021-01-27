FROM ubuntu:20.04

USER root
WORKDIR /

RUN DEBIAN_FRONTEND="noninteractive"

RUN apt-get update && apt-get install -y build-essential && \
    apt-get install -y g++ make cmake vim git libgtk2.0-dev pkg-config \
    libavcodec-dev libavformat-dev libswscale-dev && \
    apt-get install -y python3-dev python3-pip python3-numpy ipython -y libtbb2 \
    libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev \
    && apt-get clean && rm -rf /var/lib/apt-lists/*

ARG OPENCV_VERSION=4.5.1
RUN wget -q -O opencv-${OPENCV_VERSION}.tar.gz https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.tar.gz && \
    wget -q -O opencv_contrib-${OPENCV_VERSION}.tar.gz https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.tar.gz && \
    tar -xvf opencv-${OPENCV_VERSION}.tar.gz && \
    tar -xvf opencv_contrib-${OPENCV_VERSION}.tar.gz &&\
    cd /opencv-${OPENCV_VERSION} && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-${OPENCV_VERSION}/modules \
      -DBUILD_EXAMPLES=OFF -DINSTALL_TESTS=OFF -DBUILD_opencv_python2=OFF \
      -DBUILD_opencv_python3=ON -DPYTHON3_EXECUTABLE=/usr/bin/python3 \
      -DENABLE_PRECOMPILED_HEADERS=OFF -DWITH_CUDA=ON .. \
      -DOPENCV_GENERATE_PKGCONFIG=ON -DWITH_CUDNN=ON \
      -DOPENCV_DNN_CUDA=ON && \
    make && \
    make install && \
    cd / && \
    rm  -rf opencv-${OPENCV_VERSION}.tar.gz opencv_contrib-${OPENCV_VERSION}.tar.gz opencv-${OPENCV_VERSION} opencv_contrib-${OPENCV_VERSION}


RUN apt-get install -y automake ca-certificates libtool autoconf zlib1g-dev

ARG TESSERACT_VERSION=4.5.1
RUN wget -q -O tesseract-${TESSERACT_VERSION}.tar.gz https://github.com/tesseract-ocr/tesseract/archive/4.1.1.tar.gz && \
    tar -xvf tesseract-${TESSERACT_VERSION}.tar.gz && \
    cd /tesseract-${TESSERACT_VERSION} && ./autogen.sh && ./configure --prefix=/usr/local/ && make && make install && ldconfig && \
    cd / && \
    rm  -rf tesseract-${TESSERACT_VERSION}.tar.gz tesseract-${TESSERACT_VERSION}.tar.gz


CMD ["/bin/bash"]
