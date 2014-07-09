#!/bin/bash
cd OSGi-bundle/bin/
zip -r bundle_test * 
mv bundle_test.zip ../../OSGi-plateform/bundle_test.jar
