#!/bin/bash

cp ./dochybrid/doc.pdf documentation.pdf

zip -R HeitorWerneckTP3.zip README.md Makefile Dockerfile CMakeLists.txt .dockerignore documentation.pdf test/* src/*

rm documentation.pdf
