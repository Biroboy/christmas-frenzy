#!/bin/bash

killall WS2812_Run

COLOUR=`echo "$QUERY_STRING" | sed -n 's/^.*lightColour=\([^&]*\).*$/\1/p' | sed "s/%23/0x/g"`
PATTERN=`echo "$QUERY_STRING" | sed -n 's/^.*pattern=\([^&]*\).*$/\1/p'` 

daemon -- /smbShare/build/ws2812b/WS2812_Run -p$PATTERN -c$COLOUR &
disown $!


printf "Content-type: text/html\n\n"
printf "<html><head><title>What You Said</title></head>"
printf "<body>Here's what you said:<br>"
printf "You entered $PATTERN for the desired pattern.<br>"
printf "You entered $COLOUR for the desired colour."
printf "</body></html>"

