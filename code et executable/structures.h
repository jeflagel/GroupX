#ifndef projet_structures
#define projet_structures
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NOMBRE_PERSONNE ;
int TAILLE_GROUPE ;
int NOMBRE_GROUPE ;

typedef struct personne
{
	int taille ; 
	char dateIns[11];
	char qualite[9];
	char adresse [70];
	char CodeP[8]; 
	char Ville[20];
	char dateNaiss [20];
	char telephone[15];
	char mail[50];
	char nom[40];
	char prenom[30];
	int groupe ; 
	int tab[4];
	char IRC[4];
	char poids[6] ;
	char taillePers[7];  
	 
	struct personne * sup ;
	struct personne * suivante ;
}personne_h ;


personne_h* creationPersonne();
void liberation(personne_h **courant);
void RenduCSV(personne_h *tete, FILE * fp);
void affichageL(personne_h *tete);
void affichageGroupe(personne_h **tab, personne_h *tete, personne_h *debut);

#endif


