# christmas-frenzy
Christmas light controller and web interface.

Basic requirements:
1) Raspberry Pi - Kinda required for this project.
2) WS2812b LED String
   - Connect the WS2812b's Data_IN pin to the RaspPi's SPI MOSI pin
   - Connect the WS2812b's GND pin to one of the GND pins on the RaspPi GPIO Header
   - Use an external 5V supply to power the WS2812b's
   - DO NOT POWER THE WS2812B STRING FROM THE RASPBERRY PI. YOU WILL FRY IT'S POWER SUPPLY!
3) WiringPi library installed
   - It's how I drive the SPI to talk to the LEDs
4) Apache2 installed
   - Apache gives us our external interface
   - Make sure you've enabled the cgi-bin module
   - This is not designed to be a publicly-facing website. It's designed so you can use your phone to control your lights when you're on your own WiFi.
5) (Optional) CMake installed
   - The C++ app has a CMakeLists.txt file to make it easy to build. Up to you if you just want to G++ it yourself.

This repo includes 3 folders.
 * The <HTML> folder contains the basic control page.
   - The form submit targets may need to be changed to match your CGI-BIN config.
 * the <CGI-BIN> folder contains the bash scripts that run the light control process.
   - The path to the light controller will need to be changed to wherever the binary ends up
 * the <CPP-SRC> folder contains the C++ source for my little demo app
   - All the source is in a single project
   - The included CMakeLists.txt should work for you
   - If you want to add new patterns, just add new state functions to the state machine in this code.

