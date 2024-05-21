FROM ubuntu:22.04

RUN apt update && \
    apt install -y wget build-essential autoconf automake libtool

RUN mkdir /project

# Download and build CppUTest
RUN mkdir /project/tools/ && \
    cd /project/ && \
    wget https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz && \
    tar xf cpputest-4.0.tar.gz && \
    mv cpputest-4.0/ tools/cpputest/ && \
    cd tools/cpputest/ && \
    autoreconf -i && \
    ./configure && \
    make

COPY src /project/src
COPY tests /project/tests
COPY Makefile /project/Makefile

ENTRYPOINT ["make", "test", "-C", "/project/"]
