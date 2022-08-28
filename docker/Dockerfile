FROM ev3dev/debian-stretch-cross:latest

RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.0/cmake-3.24.0.tar.gz
RUN tar -zxvf cmake-3.24.0.tar.gz
RUN cd cmake-3.24.0 && \
    sudo apt-get update -y && \
    sudo apt-get install -y build-essential && \
    sudo apt-get install -y libssl-dev && \
    ./bootstrap && \
    make -j $(nproc) && \
    sudo apt-get remove --purge cmake -y && \
    sudo make install && \
    rm -r *