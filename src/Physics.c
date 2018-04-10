#include "Physics.h"
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
extern RNG_HandleTypeDef hrng;
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
//unsigned char ucCheckCollision(unsigned char par_Pos_X, unsigned char par_Pos_Y, const unsigned char* par_Array_Bmp)
//{
//  int iIndex_Bmp = 0;
//  int iPos_Page_Y = 0; // Position dans la page active (0~7).
//  int iMasque = 0;
//  iIndex_Bmp = par_Pos_X + (par_Pos_Y * 128); 
//  
//  iPos_Page_Y = par_Pos_Y % 8;
//  iMasque = ldexp(1, iPos_Page_Y);
//  if((par_Array_Bmp[iIndex_Bmp] & iMasque) == 0)
//    return P_NO_COLLISION;
//  else
//    return P_COLLISION;      
//}

void vNewVector(float *Balle_X, float *Balle_Y, float Mur_X, float Mur_Y)
{
  *Balle_X += Mur_X;
  *Balle_Y += Mur_Y;
}

void vStartVector(float *Balle_X, float *Balle_Y)
{
  uint32_t lRandom = 0;
  HAL_RNG_GenerateRandomNumber(&hrng, &lRandom);
  srand((uint16_t) lRandom);
  do
    *Balle_X = ((float) rand()/(float)RAND_MAX) * 1.5;
  while(*Balle_X < 0.5);
  *Balle_Y = sqrt(2.25 - (pow(*Balle_X, 2)));
  if(rand()%2) *Balle_X *= -1;
}

unsigned char ucCheckIsBallOK(float *X, float *Y, float *Paddle_L, float *Paddle_R, float *P_L_Vec, float *P_R_Vec, float *Vec_X, float *Vec_Y)
{
  if(*X<3.0)
  {
    *X = 63.0;
    *Y = 31.0;
    vStartVector(Vec_X, Vec_Y);
    return BUT_J_DROIT;
  }
  else if(*X>=125.0)
  {
    *X = 63.0;
    *Y = 31.0;
    vStartVector(Vec_X, Vec_Y);
    return BUT_J_GAUCHE;
  }
  else if((*X >= 6) && (*X <= 7))
  {
    if((*Y>=*Paddle_L-3) && (*Y <= *Paddle_L + PADDLE_SIZE+3))
      vNewVector(Vec_X, Vec_Y, PADDLE_VEC_X, *P_L_Vec);
    return HIT_PAD_L;
  }
  else if((*X >= 121) && (*X <= 122))
  {
    if((*Y>=*Paddle_R-3) && (*Y <= *Paddle_R + PADDLE_SIZE+3))
      vNewVector(Vec_X, Vec_Y, PADDLE_VEC_X, *P_R_Vec);
    return HIT_PAD_R;
  }
  else if(*Y<=2.0) // ROOF
  {
    *Y = 3.0;
    vNewVector(Vec_X, Vec_Y, MUR_HAUT_VEC_X, MUR_HAUT_VEC_Y);
    return HIT_ROOF;
  }
  else if(*Y>=61.0) // Floor
  {
    *Y = 60.0;
    vNewVector(Vec_X, Vec_Y, MUR_BAS_VEC_X, MUR_BAS_VEC_Y);
    return HIT_FLOOR;
  }

  else
    return BALL_OK;
}

void vAI(float Balle_X, float Balle_Y, float Pos_Y, float *Vecteur, unsigned char pos, unsigned char sense)
{
  if(sense == 'G')
  {
    if(Balle_X < pos)
    {
      if(Balle_Y < (Pos_Y + 8))
        *Vecteur = -1.0f;
      else if(Balle_Y > (Pos_Y +8))
        *Vecteur = 1.0f;
      else 
        *Vecteur = 0;
    }
  }
  else 
  {
    if(Balle_X > pos)
    {
      if(Balle_Y < (Pos_Y + 8))
        *Vecteur = -1.0f;
      else if(Balle_Y > (Pos_Y +8))
        *Vecteur = 1.0f;
      else 
        *Vecteur = 0;
    }
  }
}