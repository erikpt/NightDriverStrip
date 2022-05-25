//+--------------------------------------------------------------------------
//
// File:        ledmatrixgfx.cpp
//
// NightDriverStrip - (c) 2018 Plummer's Software LLC.  All Rights Reserved.  
//
// This file is part of the NightDriver software project.
//
//    NightDriver is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//   
//    NightDriver is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//   
//    You should have received a copy of the GNU General Public License
//    along with Nightdriver.  It is normally found in copying.txt
//    If not, see <https://www.gnu.org/licenses/>.
//
// Description:
//
//    Code for handling HUB75 matrix panels
//
// History:     May-24-2021         Davepl      Commented
//
//---------------------------------------------------------------------------

#include "gfxbase.h"
#include "globals.h"

uint32_t GFXBase::noise_x;
uint32_t GFXBase::noise_y;
uint32_t GFXBase::noise_z;
uint32_t GFXBase::noise_scale_x;
uint32_t GFXBase::noise_scale_y;

uint8_t GFXBase::noise[MATRIX_WIDTH][MATRIX_HEIGHT];   // BUGBUG Could this go in PSRAM if allocated instead?
uint8_t GFXBase::noisesmoothing;

#ifdef USEMATRIX

  #include <SmartMatrix.h>
  #include "ledmatrixgfx.h"
    
  SMLayerIndexed<SM_RGB, kIndexedLayerOptions> indexedLayer(kMatrixWidth, kMatrixHeight);  
  SMLayerScrolling<SM_RGB, kScrollingLayerOptions> scrollingLayer(kMatrixWidth, kMatrixHeight);  
  SMLayerBackground<SM_RGB, kBackgroundLayerOptions> backgroundLayer(kMatrixWidth, kMatrixHeight);
  SmartMatrixHub75Refresh<COLOR_DEPTH, kMatrixWidth, kMatrixHeight, kPanelType, kMatrixOptions> matrixRefresh; 
  SmartMatrixHub75Calc<COLOR_DEPTH, kMatrixWidth, kMatrixHeight, kPanelType, kMatrixOptions> matrix;

    
void LEDMatrixGFX::StartMatrix()
{
    matrix.addLayer(&backgroundLayer);
    matrix.begin(100000);

    backgroundLayer.fillScreen(rgb24(0, 64, 0));
    backgroundLayer.setFont(font5x7);
    backgroundLayer.drawString(8, kMatrixHeight / 2 - 6, rgb24(255,255,255), "NightDriver");
    backgroundLayer.swapBuffers(false);    

    matrix.setBrightness(255);
}

CRGB * LEDMatrixGFX::GetMatrixBackBuffer()
{
    return (CRGB *) backgroundLayer.getRealBackBuffer();
}

void LEDMatrixGFX::MatrixSwapBuffers()
{
  backgroundLayer.swapBuffers(true);
}
#endif
