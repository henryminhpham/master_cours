#!/bin/bash

export MY_HADOOP_HOME=${HOME}/Java/hadoop
export PATH=${PATH}:${MY_HADOOP_HOME}/bin
cd ${MY_HADOOP_HOME}/bin
./start-all.sh
./checkStart.sh
