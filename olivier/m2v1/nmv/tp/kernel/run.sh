#!/bin/bash

qemu -hda /tmp/nmv-archlinux.img -hdb ~/myHome.img -net nic -net user -no-acpi -boot c
