FROM heitor57/alpine-mpich:onbuild

USER root
RUN apk update
RUN apk upgrade --available && sync
# bind-tools gives us 'dig'
RUN apk add --no-cache openssh bind-tools
RUN apk add --no-cache cmake openmpi
RUN apk add --no-cache bash

COPY get_hosts_mod /usr/local/bin/get_hosts_mod
RUN chmod +x /usr/local/bin/get_hosts_mod

# Install python/pip
ENV PYTHONUNBUFFERED=1
RUN apk add --update --no-cache python3 && ln -sf python3 /usr/bin/python
RUN python3 -m ensurepip
RUN pip3 install --no-cache --upgrade pip setuptools eulerlib arith_lib

USER ${USER}
#docker pull 
#FROM ubuntu:20.04
#ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Sao_Paulo"
COPY project/ .
#RUN rm /bin/sh && ln -s /bin/bash /bin/sh
#RUN apt-get update && apt-get install -y \
    #build-essential \
    #curl \
    #cmake \
    #openmpi-bin
USER root
RUN chmod -R 777 .
USER ${USER}
RUN make
#RUN get_hosts > hostfile

#CMD ["/bin/bash"]
CMD bash
#FROM heitor57/alpine-mpich:onbuild

## # ------------------------------------------------------------
## # Build MPI project
## # ------------------------------------------------------------

## Put all build steps and additional package installation here

## Note: the current directory is ${WORKDIR:=/project}, which is
## also the default directory where ${USER:=mpi} will SSH login to

## Copy the content of `project` directory in the host machine to 
## the current working directory in this Docker image
#COPY project/ .

## Normal build command
#RUN mpicc -o mpi_hello_world mpi_hello_world.c

## ####################
## For Docker beginner:

## After Docker syntax `RUN`, you can execute any command available in 
## the current shell of the image.

## To switch to root:    USER root
## To switch back to default user: USER ${USER}
