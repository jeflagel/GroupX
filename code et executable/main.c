#include "affectation.h"

int main(){
	FILE *fp;
	int erreur = 0;
	personne_h* tete = NULL;
	personne_h* fin = NULL;
	personne_h* debut = creationPersonne();
	int* Tab_Groupe;
	int  max = 0 ;
	personne_h **Tab_Groupe_Chainee;
	if((fp=fopen("source.csv", "r"))==NULL)   /*Ouvre une première fois le fichier pour compter le nombre de personnes répertoriées*/
	{
		printf("Le nom du fichier excel est incorrect. Veuillez le renommer source.csv.\n");
		erreur = 1;
	}
	else
	{
		NOMBRE_PERSONNE = CalculNombrePersonne(fp);
		fclose(fp);
	}
	if((fp=fopen("source.csv", "r"))==NULL)   /*Ouvre une seconde fois le fichier pour enregistrer les personnes dans une liste chainée*/
	{
		printf("Le nom du fichier excel est incorrect. Veuillez le renommer source.csv.\n");
		erreur = 1;
	}
	else
	{
		lecture(fp, &tete, &fin, &debut, &max);
		fclose(fp);
	}
	if(!erreur){
		if(NOMBRE_GROUPE < max){
                   /*Vérifie que le nombre de Groupe saisie dans excel est correct*/
			printf("Il y a une erreur de saisie dans le tableau excel.\nLe nombre de groupes n'est pas correct.\nUne personne formule un voeu demandant un groupe supérieur aux nombres de groupes.\n Veuillez rectifier.\n Si une personne n'a qu'un seul voeu, veuillez remplir les 4 voeux par cette valeur.\n");
		}
		else{
			if(TAILLE_GROUPE<=0){   /*Vérifie que la Taille des groupes saisie dans excel est correct*/
				printf("Il y a une erreur dans la saisie de la taille des groupes du tableau excel.\nIl faut que la taille soit positive.\nAllez vérifier dans votre tableau excel, modifiez et refaites une sauvegarde\n");
			}
			else {
				Tab_Groupe = calloc(NOMBRE_GROUPE, sizeof(int));
				Tab_Groupe_Chainee = calloc(NOMBRE_GROUPE, sizeof(personne_h*));
				InitGroupe(Tab_Groupe, Tab_Groupe_Chainee);
				affectationVoeux1(&tete, Tab_Groupe, Tab_Groupe_Chainee);
				affectationVoeux2(&tete, Tab_Groupe, Tab_Groupe_Chainee);
				affectationVoeux3(&tete, Tab_Groupe, Tab_Groupe_Chainee);
				affectationVoeux4(&tete, Tab_Groupe, Tab_Groupe_Chainee);
				affichageGroupe(Tab_Groupe_Chainee, tete, debut);
				free(Tab_Groupe);
				free(Tab_Groupe_Chainee);
				liberation(&tete);
				printf("la repartition des groupes a ete effectue avec succes.\nVous pouvez maintenant acceder au resultat dans le fichier repartition.csv.\n Appuyez sur n'importe quelle touche pour fermer la fenetre.\n");
			}
		}
	}
	free(debut);
    system("pause");
	return 0;
}
