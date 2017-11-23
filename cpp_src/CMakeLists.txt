cmake_minimum_required (VERSION 2.6)
project (cmakeTest)

file( GLOB src *.cpp )
file( GLOB hdr *.h )

add_executable( WS2812_Run ${src} )
target_link_libraries( WS2812_Run wiringPi )
