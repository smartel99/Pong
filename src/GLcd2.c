#include "stdio.h"
#include "GLcd2.h"
#include "Font.h"
#include "NiceFlag.h"
#include "stm32f4xx_hal.h"
////////////////////
// A0 -> CS1
// A1 -> CS2
// A2 -> W/R
// A3 -> DI
// A4 -> NC
////////////////////
extern unsigned char ucFontSystem3x6[65][3];
extern unsigned char ucFontSystem5x8[97][5];
extern unsigned char ucFontSystem7x8[97][7];
// ucGetOnScreenChar
// Auteur: Samuel Martel
// Date 20 mars 2018
// Description: Retourne l'indice du tableau dans font.h correspondant 
//				au caractère se trouvant à la position (ligne, colonne) passé
//				en paramètre selon le font en paramètre (3, 5 ou 7).
//				La fonction scanne le tableau correspondant au font et garde en note
//				ceux qui correspondent à la valeur retourné par l'écran, jusqu'à ce qu'il 
//				ne reste qu'un seul élément restant.
//
//				La fonction identifie les caractères correspondant en plaçant un "checkmark"
//				dans un tableau de taille identique à ceux des fonts (65 pour taille 3, 97 pour taille 5 et 7)
//				À chaque passage, la fonction vérifie le nombre de "checkmark" pour déterminer si elle doit
//				continuer de faire les comparaisons, s'il n'y a qu'un seul "checkmark", elle retourne l'indice de 
//				celui-ci.
//
//				Choisir la méthode de vérification:
//					- scanner ligne par ligne
//					- scanner chaque lettre
// 				si l'octet lue est égale à l'octet actif de la lettre active du font, place l'indice de cette lettre
// 				dans un array (ucCheckList) contenant toutes les indices des lettres.
// 				La fonction garde en note le nombre de valeurs qui correspondent dans ucNombreDeCheck.
// 				Lors du premier passage, la fonction scan toutes les lettres.
// 				Lors des passages suivant, la fonction scan les lettres dont les indices se trouvent dans l'array
// 				jusqu'à ucNombreDeCheck
// 				Si ucCheckTillMe est égale à 1, c'est qu'il ne reste que la bonne lettre, la fonction retourne donc
// 				cette lettre.
// 				Si ucCheckTillMe est égale à 0, c'est qu'il n'y a pas de lettre qui correspont au octets lues.
// 				Si ucCheckTillMe est supérieur à 1 et que la fonction a scanné toute les lettres, c'est que
// 				plusieurs caractères sont identique, la fonction retourne donc le premier caractère de l'array.
unsigned char ucGetOnScreenChar(unsigned char ligne, unsigned char colonne, unsigned char font)
{
	UC ucCheckList[97];
        UC ucArray[16];
        UC isEqual = 0;
	UC ucBytesLue[7];
	UC i = 0,j = 0;
	UC ucNombreDeCheck = 0; // Limite supérieure exclusive des caractères correspondant.
	UC ucCheckTillMe = 97;  // Limite exclusive correspondant à ucNombreDeCheck à la fin d'un passage.
	
	vReadGLcd(ucBytesLue, ligne, colonne, font);
	vFillCheckList(ucCheckList);
	
	if(font == 3)
          ucCheckTillMe = 65; // L'array ucFontSystem3x6 est 65 par 3.

	while((i < font) && (ucCheckTillMe > 1))
	{ 
          for(j = 0, ucNombreDeCheck = 0; j < ucCheckTillMe; j++)
          {
            switch(font)
            {
              case 3:
                  if(ucBytesLue[i] == ucFontSystem3x6[ucCheckList[j]][i])
                  isEqual = 1;
                break;
              case 5:
                if(ucBytesLue[i] == ucFontSystem5x8[ucCheckList[j]][i])
                  isEqual = 1;
                break;
              case 7:
                if(ucBytesLue[i] == ucFontSystem7x8[ucCheckList[j]][i])
                  isEqual = 1;
                break;
              default:
                isEqual = 0;
            }
            
            if(isEqual)
            {
              isEqual = 0;
              ucCheckList[ucNombreDeCheck] = ucCheckList[j];
              ucNombreDeCheck++;
            }
          }
          ucCheckTillMe = ucNombreDeCheck;
          ucNombreDeCheck = 0;
          i++;
	}
        sprintf((char*)ucArray, "%x             ", ucCheckList[0]);
	vPutStringGLcd(ucArray,3,7);
	return (ucCheckList[0] + 0x20);// Retourne le code ASCII du caractère.
	
}

void vFillCheckList(UC* Array)
{
	UC i;
	for(i=0; i<97; i++)
		Array[i] = i;
}

void vReadGLcd(UC* ucByteLue,UC par_ucPage,UC par_ucColonne,UC font)
{
	unsigned char ucColonne = 0;
	unsigned char ucAddModifier = 0;        // Valeur à ajouter à l'adresse (0 ou 1) dépendant du bord d'écriture (gauche ou droite)
	unsigned char i = 0;
	
	if(par_ucColonne < 64)	                // Gauche
	{
		ucAddModifier = 1;
		ucColonne = 0x40 + par_ucColonne;// Valeur a envoyer au LCD pour selectionner une colonne.
	}
	else if((par_ucColonne >= 64) && (par_ucColonne < 128))
		ucColonne = par_ucColonne;       // Pas besoin d'ajouter 0x40 puisque le bit 6 est déjà à 1 (64 -> 0100 0000).
	
	vOutputGLcd(ADRINSTRRIGHTW+ucAddModifier, par_ucPage + 0xB8); // Set la page voulue.
	vOutputGLcd(ADRINSTRRIGHTW+ucAddModifier, ucColonne);         // Set la colonne voulue.
	for(i=0;i<font;i++)
		ucByteLue[i] = ucInputGLcd(ADRDATARIGHTR+ucAddModifier);// Lit la colonne active.
}

// ucVerifyCheckList
// Auteur: Samuel Martel
// Description: Scan l'intégrité de l'array et incrémente ucCompte chaque fois
//				qu'un élément de l'array est égal à 'X'.
//				La fonction retourne le nombre de 'X' contenu dans l'array.
unsigned char ucVerifyCheckList(unsigned char* ucArray, unsigned char ucSizeOfArray)
{
	unsigned char ucCompte, i = 0;
	for(i = 0; i < ucSizeOfArray; i++)
		if(ucArray[i] != ' ') ucCompte++;
	return ucCompte;
}

// ucGetIndice
// Auteur: Samuel Martel
// Description: Retourne l'indice de l'élément de l'array contenant 'X'.
unsigned char ucGetIndice(unsigned char* ucArray, unsigned char ucTaille_Array)
{
	int i;
	for(i = 0; i < ucTaille_Array; i++)
		if(ucArray[i] != ' ') return i;
        return 0;
}

//// ucCheckArray
//// Auteur: Samuel Martel
//// Description: Compare la valeur de "temp" avec celle se trouvant dans le 
////              tableau correspondant au font à l'indice [ligne][colonne].
////              Si les deux valeurs sont identiques: retourne 1
////              Sinon: retourne 0.
//UC ucCheckArray(UC temp,UC colonne,UC ligne,UC font)
//{
//  if(font == 3)
//    if(temp == ucFont3x6[ligne][colonne]) return 1;
//  else if(font == 5)
//    if(temp == ucFont5x8[ligne][colonne]) return 1;
//  else if(font == 7)
//    if(temp == ucFont7x8[ligne][colonne]) return 1;
//  return 0;
//}

void vStartScreen(void)
{
  UC i;
  vClearGLcd(0);

  vPutBMPGLcd((unsigned char*)BestFlag);
}

void vInfoScreen(void)
{
  unsigned char ligne1[] = {"      LAB4-416.     "};
  unsigned char ligne3[] = {"   Cegep Limoilou   "};
  unsigned char ligne4[] = {"        2018        "};
  unsigned char ligne6[] = {"   Samuel Martel.   "};
  
  vClearGLcd(0);
  vPutStringGLcd(ligne1, 0, 5);
  vPutStringGLcd(ligne3, 2, 5);
  vPutStringGLcd(ligne4, 3, 5);
  vPutStringGLcd(ligne6, 5, 5);
}

void vScrollScreenUp(UC ucNombreDePage)  // ucNombreDePage [1~8]
{
  UC i,j;
  
  for(i=0; i<ucNombreDePage; i++)
  {
    for(j=0; j<8; i++)
    {
      vOutputGLcd(ADRINSTRLEFTW, (0xC0 | (i*j)));
      vOutputGLcd(ADRINSTRRIGHTW, (0xC0 | (i*j)));
    }
  }
}