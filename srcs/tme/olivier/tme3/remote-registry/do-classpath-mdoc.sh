#!/bin/bash

cd $JONAS_ROOT
echo .$(find -iname "*.jar" -printf ":\$JONAS_ROOT/%p")
