# syntax=docker/dockerfile:1
FROM nlknguyen/alpine-mpich:latest
#docker pull 
#FROM ubuntu:20.04
#ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Sao_Paulo"
COPY . /app
RUN rm /bin/sh && ln -s /bin/bash /bin/sh
#RUN apt-get update && apt-get install -y \
    #build-essential \
    #curl \
    #cmake \
    #openmpi-bin
RUN make /app
CMD bash
