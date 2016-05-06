//
//  highRessImage.h
//  freeImage
//
//  Created by Natxo Pedreira gonzalez on 6/5/16.
//
//

#ifndef freeImage_highRessImage_h
#define freeImage_highRessImage_h

#include "freeImage.h"

class highRessImage {
private:
    FIBITMAP * getBmpFromPixels(ofPixels &pix){
        
        
        FIBITMAP * bmp = NULL;
        int w						= pix.getWidth();
        int h						= pix.getHeight();
        unsigned char * pixels		= pix.getPixels();
        int bpp						= pix.getBitsPerPixel();
        int bytesPerPixel			= pix.getBitsPerPixel() / 8;
        
        
        
        // part for little endian
        unsigned char temp;
        int pos;
        for (int i = 0; i < w*h; i++){
            pos = i * 3;
            temp = pixels[pos  ];
            pixels[pos  ] = pixels[pos+2];
            pixels[pos+2] = temp;
        }//end of part
        
        bmp	= FreeImage_ConvertFromRawBits(pixels, w,h, w*3,24,0,0,0, true);
        
        return bmp;  
    }
    
public:
    void saveImage(ofImage &img, string _url){
        
        string fname = ofToDataPath(_url);
        
        FREE_IMAGE_FORMAT fif = FIF_TIFF;
        FIBITMAP * bmp	= getBmpFromPixels(img.getPixelsRef());
        
        
        FreeImage_SetDotsPerMeterX(bmp, 11811);
        FreeImage_SetDotsPerMeterY(bmp, 11811);
        
        FreeImage_Save(fif, bmp, fname.c_str(), TIFF_NONE);
    }
};

#endif
