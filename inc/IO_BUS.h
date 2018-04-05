//******************************************************************************
//   Nom du fichier : IO_BUS.h
//   Auteur : Alain Champagne                  
//      Date de cr�ation : 21-12-2015 
//        Fichier de d�claration et de d�finition des fonctions de controle des 
//        �l�ments d'entr�es sorties.
//  
//******************************************************************************
#ifndef IO_BUSH
  #define IO_BUSH

#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3

#define Level_CS0 1
#define Level_CS1 0
#define Level_CS2 0
#define Level_CS3 0

//Predeclaration des fonctions
 void vDelai_IO(unsigned char i);
 void vData_IN(void);
 void vData_OUT(void);
 unsigned char ucReadIO (unsigned char CSx, unsigned char Level, unsigned char ucAdresse);
 void vWriteIO(unsigned char ucEcrireDataIO, unsigned char CSx, unsigned char Level, unsigned char ucAdresse);



#endif
