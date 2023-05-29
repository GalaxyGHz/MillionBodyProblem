#!/bin/bash

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude -DTEST1
./main

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude -DTEST2
./main

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude -DTEST3
./main

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude -DTEST4
./main

gcc src/main.c src/drawer.c src/star.c src/cube.c src/bhTree.c -o main -w -lGL -lGLU -lglut -lm -Iinclude
./main

exit 0