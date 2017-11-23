#!/bin/bash

killall WS2812_Run


printf "Content-type: text/html\n\n"
printf "Lights Stopped!"

/smbShare/build/ws2812b/WS2812_Run -s > /dev/null
