#!/bin/bash
case "$1" in 
start)
    /usr/bin/crosscmd > /dev/null &
    echo $!>/var/run/crosscmd.pid
    ;;
stop)
    kill `cat /var/run/crosscmd.pid`
    rm /var/run/crosscmd.pid
    ;;
restart)
    $0 stop
    $0 start
    ;;
status)
    if [ -e /var/run/hit.pid ]; then
        echo crosscmd is running, pid=`cat /var/run/crosscmd.pid`
    else
        echo crosscmd is NOT running
        exit 1
    fi
    ;;
*)
    echo "Usage: $0 {start|stop|status|restart}"
esac
exit 0