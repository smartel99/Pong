#ifndef PHYSICS_H
#define PHYSICS_H

#define P_NO_COLLISION 0
#define P_COLLISION    1

#define MUR_HAUT_LOC   0
#define MUR_HAUT_VEC_X 0
#define MUR_HAUT_VEC_Y (-2 * (*Vec_Y))
    
#define MUR_BAS_LOC    63
#define MUR_BAS_VEC_X  0
#define MUR_BAS_VEC_Y  (-2 * (*Vec_Y))
    
#define MUR_GAUCHE_LOC 0
#define MUR_GAUCHE_VEC_X (-2 * (*Vec_X))
#define MUR_GAUCHE_VEC_Y 0
    
#define MUR_DROIT_LOC  127
#define MUR_DROIT_VEC_X (-2 * (*Vec_X))
#define MUR_DROIT_VEC_Y 0

#define BALL_OK         0
#define BUT_J_DROIT     1
#define BUT_J_GAUCHE    2
#define HIT_ROOF        3
#define HIT_FLOOR       4
#define BALL_NOT_TESTED 5



unsigned char ucCheckCollision(unsigned char par_Pos_X, unsigned char par_Pos_Y, const unsigned char* par_Array_Bmp);
void vNewVector(float *Balle_X, float *Balle_Y, float Mur_X, float Mur_Y);
void vStartVector(float *Balle_X, float *Balle_Y);
unsigned char ucCheckIsBallOK(float *X, float *Y, float *Vec_X, float *Vec_Y);
#endif