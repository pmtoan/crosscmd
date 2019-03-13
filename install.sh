#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo 'please run script as root'
    exit
fi

gcc -std=gnu99 -o /usr/bin/crosscmd crosscmd.c

gcc -std=gnu99 -o /usr/bin/crossctl crossctl.c

cp scripts/crosscmd.sh /etc/init.d/crosscmd.sh
chmod +x /etc/init.d/crosscmd.sh

/etc/init.d/crosscmd.sh start
