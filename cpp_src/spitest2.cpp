#include "WS2812B.h"
#include <wiringPi.h>
#include <cstdlib>
#include <cstring>
// #include <cstdio>
#include <iostream>
#include <unistd.h>

const float fillLevel = 0.10;
bool cycle = true;
bool forceColour = false;
hsv_dbl_t targetHSV = {0,0,0};
const int nSteps = 500;

void mode2_step(ws2812B_SPI *dispPtr, int count);
void mode1_step(ws2812B_SPI *dispPtr, int count);
void mode0_step(ws2812B_SPI *dispPtr, int count);

int main(int argC, char *argV[])
{
  std::cout << "STARTING!" << std::endl;
  int currentMode = 0;
  int opt;
	
  while ((opt = getopt(argC, argV, "sSp::c::")) != -1) {
    switch (opt) {
      case 'S':
      case 's':
        std::cout << "Turning off all lights!" << std::endl;
        currentMode = -1;
        break;
      case 'p':
        if(optarg != NULL){
          cycle = false;
          currentMode = strtol(optarg, NULL, 0);
          std::cout << "Forcing Mode " << currentMode << std::endl;
        }
        break;
      case 'c':
        std::cout << "TESTME!" << std::endl;
        if(optarg != NULL){
          int colourArg = strtol(optarg, NULL, 0);
          std::cout << "optarg2!" << colourArg << std::endl;
          if(colourArg != 0)
          {
            forceColour = true;
            unsigned char b = (colourArg>>0 ) % 256;
            unsigned char g = (colourArg>>8 ) % 256;
            unsigned char r = (colourArg>>16) % 256;
            rgb_dbl_t targetRGB;
            targetRGB.r = r/255.0;
            targetRGB.g = g/255.0;
            targetRGB.b = b/255.0;
            targetHSV = rgb2hsv(targetRGB);
            printf("Target RGB = R:%f B:%f G:%f\n", targetRGB.r, targetRGB.g, targetRGB.b);
            printf("Target HSV = H:%f S:%f V:%f\n", targetHSV.h, targetHSV.s, targetHSV.v);
          }
          else
            std::cout << " No Colour Arg Passed!" << std::endl;
        }
        break;
      default: // '?'
        fprintf(stderr, "Usage: %s [-pPattern] [-cColour] \n", argV[0]);
        exit(EXIT_FAILURE);
    }
  }
	
  ws2812B_SPI mySpiDisplay;
  mySpiDisplay.clearDisplay();
  
  if(currentMode == -1)
  {
	  return 0;
  }
  
  unsigned int cnt = 0;
  while(true){
	  cnt++;
	  if(cycle && (cnt >= nSteps))
	  {
		  currentMode++;
		  cnt = 0;
	  }
	  switch(currentMode)
	  {
	  case 0:
		  mode0_step(&mySpiDisplay, cnt);
		  break;
	  case 1:
		  mode1_step(&mySpiDisplay, cnt);
		  break;
	  case 2:
		  mode2_step(&mySpiDisplay, cnt);
		  break;
	  case 3:
	  default:
		  currentMode = 0;
	  }
	delay(25);
  }
  return 0;
}

void mode0_step(ws2812B_SPI *dispPtr, int count)
{
	hsv_dbl_t hue;
  if(!forceColour)
  {
    hue.s = 1;
    hue.v = 1;
    hue.h = (count*2)%360;
  }
  else
    hue = targetHSV;
	// std::cout << hue.h << std::endl;
	dispPtr->fadeAll(0.7, 16, false);
	dispPtr->setPixVal(count%16, hsv2rgb(hue), false);
  if(!forceColour)
    hue.h = (count*2 + 180)%360;
	dispPtr->setPixVal((count+8)%16, hsv2rgb(hue));
	// mySpiDisplay.setPixVal((cnt+8)%16, hsv2rgb(hue));
}

void mode1_step(ws2812B_SPI *dispPtr, int count)
{
	dispPtr->fadeAll(0.6, 16, false);

	count /= 2;
	hsv_dbl_t hue;
  if(!forceColour)
  {
    hue.s = 1;
    hue.v = 1;
    hue.h = (count*5)%360;
  }
  else
    hue = targetHSV;

	dispPtr->setPixVal(count%16, hsv2rgb(hue), false);
	if(!forceColour)
    hue.h = (count*5 + 90)%360;
	dispPtr->setPixVal((count+4)%16, hsv2rgb(hue), false);
	if(!forceColour)
    hue.h = (count*5 + 180)%360;
	dispPtr->setPixVal((count+8)%16, hsv2rgb(hue), false);
	if(!forceColour)
    hue.h = (count*5 + 270)%360;
	dispPtr->setPixVal((count+12)%16, hsv2rgb(hue));
	// mySpiDisplay.setPixVal((cnt+8)%16, hsv2rgb(hue));
}

void mode2_step(ws2812B_SPI *dispPtr, int count)
{
	hsv_dbl_t hue;
  if(!forceColour)
  {
    hue.s = 1;
    hue.v = 1;
    hue.h = (2*count)%360;
  }
  else
    hue = targetHSV;

	// std::cout << hue.h << std::endl;
	dispPtr->fadeAll(10, false);
	if(rand()%100 < 10)  dispPtr->setPixVal(rand()%16, hsv2rgb(hue));
	else                 dispPtr->refresh();

}