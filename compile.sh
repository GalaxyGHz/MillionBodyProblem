#!/bin/bash

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude

exit 0