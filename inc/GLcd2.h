#ifndef GLCD2_H
	#define GLCD2_H


#include "GLcd.h"
#include "IO_BUS.h"
#ifndef UC
  #define UC unsigned char
  #define UI unsigned int
#endif
unsigned char ucGetOnScreenChar(unsigned char ligne, unsigned char colonne, unsigned char font);
void vFillCheckList(UC* Array);
void vReadGLcd(UC* ucByteLue,UC par_ucPage,UC par_ucColonne,UC font);
unsigned char ucGetIndice(unsigned char* ucArray, unsigned char ucTaille_Array);
unsigned char ucVerifyCheckList(unsigned char* ucArray, unsigned char ucSizeOfArray);
UC ucCheckArray(UC temp,UC colonne,UC ligne,UC font);
void vStartScreen(void);
void vInfoScreen(void);
void vScrollScreenUp(UC ucNombreDePage);

#endif