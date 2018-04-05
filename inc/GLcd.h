//******************************************************************************
//   Nom du fichier : GLcd.h
//   Auteur : Alain Champagne                  
//      Date de création : 16-03-2006 
//      Date de modification pour le STM32F4 : 23-12-2015
//        Fichier de déclaration et de définission pour les fonctions de 
//        contrôle d'un écran graphique de type KS0108.
// 
//******************************************************************************


//******************************************************************************
//                            DECLARATION ET DEFINITION                         
//******************************************************************************

#ifndef XGLCD_H
  #define XGLCD_H
//Definition externe
#ifndef CS0
	#define CS0 0
	#define Level_CS0 1
#endif
#ifndef UC
  #define UC unsigned char
  #define UI unsigned int
#endif
#define ADRINSTRLEFTR 0x06
#define ADRINSTRRIGHTR 0x05                          
#define ADRINSTRLEFTW 0x02
#define ADRINSTRRIGHTW 0x01
#define ADRDATALEFTR 0x0E
#define ADRDATARIGHTR 0x0D                          
#define ADRDATALEFTW 0x0A
#define ADRDATARIGHTW 0x09
#define ADRBUSYFLAG 0x04

//Predeclaration externe                     
unsigned char ucInputGLcd(unsigned char ucAdresse);
void vOutputGLcd(unsigned char ucAdresse, unsigned char ucDonnee);
void vDelaiGLcd(unsigned int uiTemps);  
void vInitGLcd(void);
void vClearGLcd(unsigned char ucData); 
void vPutPixelGLcd(unsigned char ucX, unsigned char ucY);
void vClearPixelGLcd(unsigned char ucX, unsigned char ucY);                                             
void vDrawLineGLcd(unsigned char ucX, unsigned char ucY, unsigned char ucLong, unsigned char ucDir); 
void vDrawRectangleGLcd(unsigned char ucX1, unsigned char ucY1, unsigned char ucX2, unsigned char ucY2); 
void vDrawCircleGLcd(unsigned char ucX, unsigned char ucY, unsigned char ucRayon); 
void vRemoveCircleGLcd(unsigned char ucX, unsigned char ucY, unsigned char ucRayon);
void vPutCharGLcd(unsigned char ucChar, unsigned char ucLigne, unsigned char ucColonne, unsigned char ucFont);
void vPutStringGLcd(unsigned char ucTab[], char iLigneLcd, unsigned char ucFont);
void vPutBMPGLcd(unsigned char ucTab[]); 



#endif 

