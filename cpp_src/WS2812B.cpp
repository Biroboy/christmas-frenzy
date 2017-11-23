#include "WS2812B.h"
#include <wiringPiSPI.h>

ws2812B_SPI::ws2812B_SPI(void)
{
	wiringPiSPISetup(0,2400000);

	for(int i = 0; i < N_PIX; i++)
	{
		dispBuffer[i] = (rgb_t){0,0,0};
	}
}

void ws2812B_SPI::refresh(void)
{
	for(int i = 0; i<N_PIX; i++){
	  rgb_t pixVal = dispBuffer[i];
	  unsigned char GC = m_gamma8[pixVal.G];
	  /* I now need to spread each byte of RGB information over 3 bytes of TX data information... this is going to be painful.*/
	  unsigned char *txWriteLoc = outputBuffer + i*9;
	  /* Bytes R0, R1 and R2 */
	  *txWriteLoc     = 0b10010010 | ((GC & 0x80) >> 1) | ((GC & 0x40) >> 3) | ((GC & 0x20) >> 5);
	  *(txWriteLoc+1) = 0b01001001 | ((GC & 0x10) << 1) | ((GC & 0x08) >> 1);
	  *(txWriteLoc+2) = 0b00100100 | ((GC & 0x04) << 5) | ((GC & 0x02) << 3) | ((GC & 0x01) << 1);

	  GC = m_gamma8[pixVal.R];
	  *(txWriteLoc+3) = 0b10010010 | ((GC & 0x80) >> 1) | ((GC & 0x40) >> 3) | ((GC & 0x20) >> 5);
	  *(txWriteLoc+4) = 0b01001001 | ((GC & 0x10) << 1) | ((GC & 0x08) >> 1);
	  *(txWriteLoc+5) = 0b00100100 | ((GC & 0x04) << 5) | ((GC & 0x02) << 3) | ((GC & 0x01) << 1);

	  GC = m_gamma8[pixVal.B];
	  *(txWriteLoc+6) = 0b10010010 | ((GC & 0x80) >> 1) | ((GC & 0x40) >> 3) | ((GC & 0x20) >> 5);
	  *(txWriteLoc+7) = 0b01001001 | ((GC & 0x10) << 1) | ((GC & 0x08) >> 1);
	  *(txWriteLoc+8) = 0b00100100 | ((GC & 0x04) << 5) | ((GC & 0x02) << 3) | ((GC & 0x01) << 1);
	}
	wiringPiSPIDataRW(0, outputBuffer, N_PIX*9);
}

void ws2812B_SPI::setPixVal(int idx, rgb_t val, bool ref)
{
  dispBuffer[idx] = val;
  if(ref) refresh();
}

void ws2812B_SPI::clearDisplay(void)
{
  for(int idx = 0; idx < N_PIX; idx++){
	  dispBuffer[idx] = (rgb_t){0,0,0};
  }
  refresh();
}

void ws2812B_SPI::setPixVal(int idx, rgb_dbl_t val, bool ref)
{
  dispBuffer[idx].R = val.r*255;
  dispBuffer[idx].G = val.g*255;
  dispBuffer[idx].B = val.b*255;
  /* dispBuffer[idx].R = m_gamma8[static_cast<unsigned char>(val.r*255)];
  dispBuffer[idx].G = m_gamma8[static_cast<unsigned char>(val.g*255)];
  dispBuffer[idx].B = m_gamma8[static_cast<unsigned char>(val.b*255)]; */
  if(ref) refresh();
}

void ws2812B_SPI::fadeAll(unsigned char fadeAmnt, bool ref)
{
  for(int idx = 0; idx < N_PIX; idx++)
  {
	  if(dispBuffer[idx].R > fadeAmnt) dispBuffer[idx].R -= fadeAmnt;
	  else dispBuffer[idx].R = 0;
	  if(dispBuffer[idx].G > fadeAmnt) dispBuffer[idx].G -= fadeAmnt;
	  else dispBuffer[idx].G = 0;
	  if(dispBuffer[idx].B > fadeAmnt) dispBuffer[idx].B -= fadeAmnt;
	  else dispBuffer[idx].B = 0;
  }
  if(ref) refresh();
}

void ws2812B_SPI::fadeAll(float fadeAmnt, unsigned char thresh, bool ref)
{
  for(int idx = 0; idx < N_PIX; idx++)
  {
	  if(dispBuffer[idx].R > thresh) dispBuffer[idx].R *= fadeAmnt;
	  else dispBuffer[idx].R = 0;
	  if(dispBuffer[idx].G > thresh) dispBuffer[idx].G *= fadeAmnt;
	  else dispBuffer[idx].G = 0;
	  if(dispBuffer[idx].B > thresh) dispBuffer[idx].B *= fadeAmnt;
	  else dispBuffer[idx].B = 0;
  }
  if(ref) refresh();
}

rgb_t ws2812B_SPI::gammaCorrect(rgb_t inVal)
{
  rgb_t retVal;
  retVal.R = m_gamma8[inVal.R];
  retVal.G = m_gamma8[inVal.G];
  retVal.B = m_gamma8[inVal.B];
  
}
