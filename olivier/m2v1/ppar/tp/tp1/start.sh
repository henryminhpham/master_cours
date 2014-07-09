#!/bin/bash

mpicc -o run $1 && mpirun -n 5 run && rm run
