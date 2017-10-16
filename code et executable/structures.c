#include "structures.h"

/*Permet de creer un personne. Alloue l'espace mémoire necessaire*/
personne_h* creationPersonne(){
	int i;
	personne_h *pers = calloc(1,sizeof(personne_h));
	pers->suivante = NULL;
	pers->sup = NULL ;
	pers->taille = 1;
	for(i=0; i<4; i++){
		pers->tab[i] = 100;
	}
	pers->groupe = -1 ;
	return pers ;
}

/*Permet de libérer l'espace memoire occupé par une liste chainée*/
void liberation(personne_h **tete)
{
	personne_h *courant= *tete;
	personne_h *temp;
	while(courant!=NULL){
		temp = courant;

		if(temp->sup!=NULL){
			free(temp->sup);
		}
		courant = courant->suivante;
		free(temp);
	}
}

/*Permet d'afficher une liste chainée de personne*/
void affichageL(personne_h *tete){
	personne_h * courant = tete;
	personne_h * courant2;
	while (courant!=NULL){
		printf("%s\n",courant->nom);
		printf("%s\n",courant->prenom);
		printf(" groupe : %d\n", courant->groupe);
		printf("%d  %d  %d  %d\n", courant->tab[0], courant->tab[1], courant->tab[2], courant->tab[3]);
		courant2= (courant->sup);
		if (courant2!=NULL){
			printf("        %s\n",courant2->nom);
			printf("        %s\n",courant2->prenom);
			printf("        %s\n",courant2->adresse);
		}
		courant = courant->suivante;
	}
}


/*Permet de creer le fichier sauvegarde.csv avec les personnes réparties dans les groupes*/

void RenduCSV(personne_h *tete, FILE * fp){
	personne_h * courant = tete;
	personne_h * courant2;
	int i;
	while (courant!=NULL){
		fprintf(fp, "%s;",courant->IRC);
		fprintf(fp, "%s;",courant->dateIns);
		fprintf(fp, "%s;",courant->qualite);
		fprintf(fp, "%s;",courant->nom);
		fprintf(fp, "%s;",courant->prenom);
		fprintf(fp, "%s;",courant->adresse);
		fprintf(fp, "%s;",courant->CodeP);
		fprintf(fp, "%s;",courant->Ville);
		fprintf(fp, "%s;",courant->dateNaiss);
		fprintf(fp,"%s;",courant->telephone);
		fprintf(fp,"%s;",courant->mail);
		fprintf(fp, "%s;", courant->taillePers);
		fprintf(fp, "%s;", courant->poids);
		if(courant->groupe!=-1){
			fprintf(fp,"%d;", courant->groupe);
			i=0;
			while(courant->tab[i]!=courant->groupe){
				i++;
			}
			fprintf(fp, "%d;\n", i);
		}
		else fprintf(fp, "non affecte;\n");
		courant2= (courant->sup);
		if (courant2!=NULL){ 					/*Si la personne précédente est accompagné*/
			fprintf(fp, "%s;",courant2->IRC);
			fprintf(fp, "%s;",courant2->dateIns);
			fprintf(fp, "%s;",courant2->qualite);
			fprintf(fp, "%s;",courant2->nom);
			fprintf(fp, "%s;",courant2->prenom);
			fprintf(fp, "%s;",courant2->adresse);
			fprintf(fp, "%s;",courant2->CodeP);
			fprintf(fp, "%s;",courant2->Ville);
			fprintf(fp, "%s;",courant2->dateNaiss);
			fprintf(fp,	"%s;",courant2->telephone);
			fprintf(fp,	"%s;",courant2->mail);
			fprintf(fp, "%s;", courant2->taillePers);
			fprintf(fp, "%s;", courant2->poids);
			if(courant->groupe!=-1){
				fprintf(fp,	"%d;", courant->groupe);
				fprintf(fp, "%d;\n", i);
			}
			else fprintf(fp, "non affecte;\n");
		}
		courant = courant->suivante;
	}
}


/*Affichage des personnes des différents groupes*/

void affichageGroupe(personne_h **tab, personne_h *tete, personne_h *debut){
	int i ;
	FILE* fp = fopen("repartition.csv", "w");
	if(fp!=NULL){
		fprintf(fp, "%s;",debut->IRC);
		fprintf(fp, "%s;",debut->dateIns);
		fprintf(fp, "%s;",debut->qualite);
		fprintf(fp, "%s;",debut->nom);
		fprintf(fp, "%s;",debut->prenom);
		fprintf(fp, "%s;",debut->adresse);
		fprintf(fp, "%s;",debut->CodeP);
		fprintf(fp, "%s;",debut->Ville);
		fprintf(fp, "%s;",debut->dateNaiss);
		fprintf(fp,"%s;",debut->telephone);
		fprintf(fp,"%s;",debut->mail);
		fprintf(fp, "%s;",debut->taillePers);
		fprintf(fp, "%s;",debut->poids);
		fprintf(fp,"\n");
		for(i=0; i<NOMBRE_GROUPE; i++){
			RenduCSV(tab[i], fp);
			liberation(&tab[i]);
		}
		RenduCSV(tete, fp);
	}
	fclose(fp);
}
