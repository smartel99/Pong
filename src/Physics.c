#include "Physics.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// ucCheckCollision
// Auteur: Samuel Martel                                          Date: 04-04-18
// Description: Determine l'etat (ON ou OFF) du pixel se trouvant a la coordonne
//              (par_Pos_X, par_Pos_Y) dans l'image par_Array_Bmp.
// Parametres d'entres:
//            - par_Pos_X -> position en X (0~127)
//            - par_Pos_Y -> position en Y (0~63)
//            - par_Array_Bmp -> image a analyser
// Parametre sortie:
//            - P_COLLISION si le pixel se trouvant a (par_Pos_X, par_Pos_Y) est
//              a 1. (valeur de 1)
//            - P_NO_COLLISION si le pixel se trouvant a (par_Pos_X, par_Pos_Y) 
//              est a 0. (valeur de 0)
// Exemple d'appelle:
//      ucEtat = ucCheckCollision(X, Y, image);
////////////////////////////////////////////////////////////////////////////////
unsigned char ucCheckCollision(unsigned char par_Pos_X, unsigned char par_Pos_Y, const unsigned char* par_Array_Bmp)
{
  int iIndex_Bmp = 0;
  int iPos_Page_Y = 0; // Position dans la page active (0~7).
  int iMasque = 0;
  iIndex_Bmp = par_Pos_X + (par_Pos_Y * 128); 
  
  iPos_Page_Y = par_Pos_Y % 8;
  iMasque = ldexp(1, iPos_Page_Y);
  if((par_Array_Bmp[iIndex_Bmp] & iMasque) == 0)
    return P_NO_COLLISION;
  else
    return P_COLLISION;      
}