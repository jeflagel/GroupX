#ifndef projet_structures2
#define projet_structures2

#include "structures.h"

                                                                      
void ViderBuffer ();

void lire_entre_Point_Virgule(char *s, FILE * fp);
int max (int a, int b, int c, int d, int  maxi);
int CalculNombrePersonne(FILE *fp);
void RecupPersonne(FILE* fp, personne_h* pers, int *max);
void lecture(FILE* fp, personne_h ** tete, personne_h ** fin, personne_h ** debut, int * max);
void InitGroupe(int * tab, personne_h** tab_chaine);
personne_h* suppression(personne_h ** prec, personne_h **tete);
void insertion(personne_h *pers, personne_h** tab);
void affectationVoeux1(personne_h **tete, int * tab_groupe, personne_h ** tab_chaine);
void affectationVoeux2(personne_h **tete, int *tab_groupe, personne_h ** tab_chaine);
int Voeux2Possible(personne_h ** tete, int num, int *tab_groupe, personne_h** tab_chaine, int length);
void affectationVoeux3(personne_h **tete, int *tab_groupe, personne_h **tab_chaine);
int Voeux3Possible(personne_h ** tete, int num, int *tab_groupe, personne_h** tab_chaine, int length);
void affectationVoeux4(personne_h **tete, int *tab_groupe, personne_h **tab_chaine);

#endif



