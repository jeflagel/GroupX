#include "affectation.h"

/*Fonction de recuperation de donnees entre deux point virgules*/
void lire_entre_Point_Virgule(char *s, FILE * fp){
	int i =0;
	char c ;
	while((c=fgetc(fp))!=';'){
	   s[i] = c ;
	   i++;
	  }
 }

/*Calcul le nombre de personne qu'il y a dans le tableau Excel*/
int CalculNombrePersonne(FILE *fp){
	char c;
	int i = 0;
	while((c=fgetc(fp))!=EOF){
		if(c=='\n'){
			i++;
		}
	}
return i-2;
}

/*Fonction de récupération de la deuxième ligne du fichier contenant le nom des colonnes*/
void RecupDebut(FILE*fp, personne_h* pers){
	char* temp = malloc(sizeof(char)*50);
	lire_entre_Point_Virgule(pers->IRC, fp);
	lire_entre_Point_Virgule(pers->dateIns, fp);
	lire_entre_Point_Virgule(pers->qualite, fp);
	lire_entre_Point_Virgule(pers->prenom, fp);
	lire_entre_Point_Virgule(pers->nom, fp);
	lire_entre_Point_Virgule(pers->adresse, fp);
	lire_entre_Point_Virgule(pers->CodeP, fp);
	lire_entre_Point_Virgule(pers->Ville, fp);
	lire_entre_Point_Virgule(pers->dateNaiss, fp);
	lire_entre_Point_Virgule(pers->telephone, fp);
	lire_entre_Point_Virgule(pers->mail, fp);
	lire_entre_Point_Virgule(pers->taillePers, fp);
	lire_entre_Point_Virgule(pers->poids, fp);
	fgets(temp, 50, fp);
	free(temp);
}

/*Fonction qui donne le maximum de cinq voeux*/
int max (int a, int b, int c, int d, int  maxi){
	if(a>maxi)
		maxi = a ;
	if(b>maxi)
		maxi = b ;
	if(c>maxi)
		maxi = c ;
	if(d>maxi)
		maxi = d ;
  return maxi;
}

/*Fonction de recuperation d'une personne (d'une ligne de fichier)*/

void RecupPersonne(FILE* fp, personne_h* pers, int* maxi)
{

	char *voeux1= calloc(4,sizeof(char));
	char *voeux2 = calloc(4,sizeof(char)) ;
	char *voeux3=calloc(4,sizeof(char));
	char *voeux4= calloc(4,sizeof(char));
	lire_entre_Point_Virgule(pers->IRC, fp);
	lire_entre_Point_Virgule(pers->dateIns, fp);
	lire_entre_Point_Virgule(pers->qualite, fp);
	lire_entre_Point_Virgule(pers->prenom, fp);
	lire_entre_Point_Virgule(pers->nom, fp);
	lire_entre_Point_Virgule(pers->adresse, fp);
	lire_entre_Point_Virgule(pers->CodeP, fp);
	lire_entre_Point_Virgule(pers->Ville, fp);
	lire_entre_Point_Virgule(pers->dateNaiss, fp);
	lire_entre_Point_Virgule(pers->telephone, fp);
	lire_entre_Point_Virgule(pers->mail, fp);
	lire_entre_Point_Virgule(pers->taillePers, fp);
	lire_entre_Point_Virgule(pers->poids, fp);
	pers->taille = 1;
	lire_entre_Point_Virgule(voeux1, fp);
	lire_entre_Point_Virgule(voeux2, fp);
	lire_entre_Point_Virgule(voeux3, fp);
	lire_entre_Point_Virgule(voeux4, fp);
	printf("%s %d ",pers->nom, *maxi);
	if(atoi(voeux1)!=0)
		pers->tab[0]= atoi(voeux1);
	if(atoi(voeux2)!=0)
		pers->tab[1]= atoi(voeux2);
	if(atoi(voeux3)!=0)
		pers->tab[2]= atoi(voeux3);
	if(atoi(voeux4)!=0)
		pers->tab[3]= atoi(voeux4);
	*maxi = max(pers->tab[0], pers->tab[1], pers->tab[2], pers->tab[3], *maxi);
	pers->sup=NULL;
	free(voeux1);
	free(voeux2);
	free(voeux3);
	free(voeux4);
	voeux1= NULL;
	voeux2=NULL;
	voeux3=NULL;
	voeux4=NULL;
 }


 /*Fonction de creation de la liste chainee*/

void lecture(FILE* fp, personne_h ** tete, personne_h ** fin, personne_h **debut, int *max)
{
	int i= 0 ;
	personne_h* pers = creationPersonne();
	personne_h * pers2 = creationPersonne();
	char *poubelle = calloc(50,sizeof(char));
	char *temp = calloc(50,sizeof(char));
	char *nbGroupe = calloc(5, sizeof(char));
	char *tailleG = calloc(5, sizeof(char));
	lire_entre_Point_Virgule(poubelle, fp);    /*Recupere "Nombre de groupe"*/
	lire_entre_Point_Virgule(nbGroupe, fp);    /*Recupere la valeur de "Nombre de Groupe"*/
	NOMBRE_GROUPE = atoi(nbGroupe);
	lire_entre_Point_Virgule(poubelle, fp);    /*Récuperer "taille groupes"*/
	lire_entre_Point_Virgule(tailleG, fp);     /*Recupere la valeur de "taille groupes"*/
	TAILLE_GROUPE = atoi(tailleG);
	fgets(poubelle, 50, fp);                  /*Recupere les ";" de la premiere ligne et passe à la suivante*/
	RecupDebut(fp, *debut);                  /*Stoke dans debut les catégories des colonnes excel*/
	(*tete) = pers ;
	(*fin) = pers;
	do{
		RecupPersonne(fp, pers, max);       /*Recupere les personnes*/
		fgets(temp,50, fp);
		if(strlen(temp)>5){  /*Verifie si elle est liée à une autre personne*/
			RecupPersonne(fp, pers2, max);
			fgets(poubelle,50, fp);  /*Passe a la ligne suivante*/
			pers->sup = pers2;       /*associe les personnes*/
			pers->taille ++ ;
			pers2 =creationPersonne();
			i++;
		}
		i++;
	   (*fin)->suivante = pers ;
	   (*fin) = pers;
	    pers = creationPersonne();
	    free(temp);
	    temp = calloc(50,sizeof(char));
	}while(i<NOMBRE_PERSONNE);
	free(temp);
	free(poubelle);
	free(nbGroupe);
	free(tailleG);
	free(pers);
	free(pers2);
}


/*Initialiste des tableaux de groupes : */
/* tab : gere la taille des groupes*/
/* tab_chainee : gere les personnes affectees aux groupes*/
void InitGroupe(int * tab, personne_h** tab_chaine)
{
	int i ;
	for(i=0; i<NOMBRE_GROUPE; i++){
		tab[i]= TAILLE_GROUPE;
		tab_chaine[i]= NULL;
	}
}

/*Supprime une personne de la liste chainee*/
personne_h* suppression(personne_h ** prec, personne_h **tete)
{
	personne_h *temp;
	if ((*prec)== NULL){
		temp = (*tete);
		(*tete) = (*tete)->suivante;
	}
	else{

		temp= (*prec)->suivante;
		(*prec)->suivante = (*prec)->suivante->suivante;

		}
	return temp;
}

/*Insere une personne dans un groupe*/
void insertion(personne_h *pers, personne_h** tab)
{
	if ((*tab)==NULL){
		pers->suivante = NULL;
		(*tab) = pers;
	}
	else {
		pers->suivante = (*tab)->suivante;
		(*tab)->suivante = pers ;
	}
}

/*Affecte un maximum de personnes dans leur voeux 1*/

void affectationVoeux1(personne_h **tete, int * tab_groupe, personne_h ** tab_chaine)
{
	personne_h * courant = (*tete) ;
	personne_h * prec = NULL;
	personne_h * temp ;
	while (courant!=NULL){
		if(tab_groupe[(courant->tab[0])-1]>= courant->taille){
																/*Verifie qu'il y a assez de place dispo dans le groupe*/
			courant->groupe = courant->tab[0];										/*Met a jour le groupe de la personne*/
			tab_groupe[(courant->tab[0])-1] = tab_groupe[(courant->tab[0])-1]-courant->taille;		/*Modifie la taille du groupe*/
			courant= courant->suivante;
			temp = suppression(&prec, tete);										/*Supprime la personne de la liste chainée*/
			insertion(temp, &(tab_chaine[(temp->tab[0])-1]));						/*insertion de la personne dans le groupe*/
		}
		else {
			prec= courant; 											/*Passage à la personne suivante sans affectation*/
			courant= courant->suivante;
		}
	}
}

/*Affectation d'un maximum de personne non affectée à leur voeux 2 */
void affectationVoeux2(personne_h **tete, int *tab_groupe, personne_h ** tab_chaine)
{
	personne_h * courant = (*tete) ;
	personne_h * prec = NULL;
	personne_h * temp ;
	while (courant!=NULL){
		if(tab_groupe[(courant->tab[1])-1]>= courant->taille){
				tab_groupe[(courant->tab[1])-1] -= courant->taille;
				courant->groupe = courant->tab[1];
				courant= courant->suivante;
				temp = suppression(&prec, tete);
				insertion(temp,&(tab_chaine[(temp->tab[1])-1]));
		}
		else{
			prec= courant;
			courant= courant->suivante;
		}
	}
}

/*Si une personne a eu son voeux un et qu'elle peut avoir une place dans son voeux 2 alors on la change de groupe*/
int Voeux2Possible(personne_h ** tete, int num, int *tab_groupe, personne_h** tab_chaine, int length)
{
	personne_h* courant = (*tete) ;
	personne_h * prec = NULL;
	personne_h * temp;
	int stop = 1 ;
	while(stop && (courant!=NULL)){
		if(((courant->tab[0])== num) && (courant->taille == length)){   /*Verif taille et personne ici pour son voeux 1*/
			if(tab_groupe[(courant->tab[1])-1]>= courant->taille){		/*Verif il y a de la place dans son voeux 2*/
				stop = 0;
			}
		}
		if(stop){														/*La personne ne repond pas au critere, passage a la suivante*/
			prec = courant ;
			courant= courant->suivante;
		}
	}
	if(!stop){															/*Nous avons trouvé une personne qui correspond*/
		temp = suppression(&prec, tete);
		temp->groupe = temp->tab[1];									/*Nous la supprimons de son groupe actuel*/
		insertion(temp, &(tab_chaine[(temp->tab[1])-1]));			/*La rajoutons dans son voeux 2*/
		tab_groupe[num-1]+=  temp->taille; 				/*Ajout de sa taille dans le groupe de depart*/
		tab_groupe[(temp->tab[1])-1]-= temp->taille; 				/*Soustraction de sa taille dans le groupe d'arrivé*/
	}
	return stop;
}

/*Affectation des personnes restantes*/
/*Si dans le groupe correspondant à leur voeux1 une personne ayant eu son voeux 1 peut etre deplacée vers son voeux 2*/
/*Alors nous la déplacons et mettons la personne courant dans son voeux 1*/
void affectationVoeux3(personne_h **tete, int *tab_groupe, personne_h **tab_chaine)
{
	personne_h * courant = (*tete) ;
	personne_h * prec = NULL;
	int verif;
	personne_h *temp ;
	while (courant!=NULL){
		verif = Voeux2Possible(&tab_chaine[(courant->tab[0])-1], courant->tab[0], tab_groupe, tab_chaine, (courant->taille));
		if(!verif){
			courant=courant->suivante;
			temp = suppression(&prec, tete);                                                    /*Une personne peut etre échangée */
			insertion(temp,&(tab_chaine[(temp->tab[0])-1]));									/* insertion dans son voeux 1*/
			temp->groupe = temp->tab[0];													/*modif taille groupe*/
			tab_groupe[(temp->tab[0])-1] = tab_groupe[(temp->tab[0])-1]-temp->taille;
		}
		else {
			if(tab_groupe[(courant->tab[2])-1]>= courant->taille){
				courant = courant->suivante;													/*Insertion du courant dans son voeux 3*/
				temp = suppression(&prec, tete);
				insertion(temp, &(tab_chaine[(temp->tab[2])-1])); 								/*Personne n'est dispo pour echanger*/
				tab_groupe[(temp->tab[2])-1] = tab_groupe[(temp->tab[2])-1]-temp->taille;	/*Modif Taille groupe*/
				temp->groupe = temp->tab[2];

			}
			else {
				prec = courant;
				courant = courant->suivante;
			}
		}
	}
}

/*Si une personne a eu son voeux un ou tab_chaine[(courant->tab[0])-1] et qu'elle peut avoir une place dans son voeux 3 alors on la change de groupe*/
int Voeux3Possible(personne_h ** tete, int num, int *tab_groupe, personne_h** tab_chaine, int length)
{
	personne_h* courant = (*tete) ;
	personne_h * prec = NULL;
	personne_h * temp;
	int stop = 1 ;
	while(stop && (courant!=NULL)){
		if((((courant->tab[0])== num)  || ((courant->tab[1])== num)) && (courant->taille == length)){   /*Verif taille et personne ici pour son voeux 1 ou 2*/
			if(tab_groupe[(courant->tab[2])-1]>= courant->taille){		/*Verif il y a de la place dans son voeux 3*/
				stop = 0;
			}
		}
		if(stop){														/*La personne ne repond pas au critere, passage a la suivante*/
			prec = courant ;
			courant= courant->suivante;
		}
	}
	if(!stop){															/*Nous avons trouvé une personne qui correspond*/
		temp = suppression(&prec, tete);
		temp->groupe = temp->tab[2];								/*Nous la supprimons de son groupe actuel*/
		insertion(temp, &(tab_chaine[(temp->tab[2])-1]));			/*La rajoutons dans son voeux 3*/
		tab_groupe[num-1]= tab_groupe[num-1] + temp->taille; 				/*Ajout de sa taille dans le groupe de depart*/
		tab_groupe[(temp->tab[2])-1]-= temp->taille; 				/*Soustraction de sa taille dans le groupe d'arrivé*/
	}
	return stop;
}


void affectationVoeux4(personne_h **tete, int *tab_groupe, personne_h **tab_chaine)
{
	personne_h * courant = (*tete) ;
	personne_h * prec = NULL;
	int verif;
	personne_h *temp ;
	while (courant!=NULL){
		verif = Voeux3Possible(&tab_chaine[(courant->tab[0])-1], courant->tab[0], tab_groupe, tab_chaine, (courant->taille));
		if(!verif){
			courant = courant->suivante;
			temp = suppression(&prec, tete);
			insertion(temp,&(tab_chaine[(temp->tab[0])-1]));							/* insertion dans son voeux 1*/
			temp->groupe = temp->tab[0];                                                  /*Une personne peut etre échangée */
			tab_groupe[(temp->tab[0])-1] = tab_groupe[(temp->tab[0])-1]-temp->taille;  /*modif taille groupe*/


		}
		else {
			verif = Voeux2Possible(&tab_chaine[(courant->tab[1])-1], courant->tab[1], tab_groupe, tab_chaine, (courant->taille));
			if(!verif){
				courant = courant->suivante;
				temp = suppression(&prec, tete);                                                    /*Une personne peut etre échangée */
				insertion(temp,&(tab_chaine[(temp->tab[1])-1]));									/* insertion dans son voeux 2*/
				temp->groupe = temp->tab[1];
				tab_groupe[(temp->tab[1])-1] = tab_groupe[(temp->tab[1])-1]-temp->taille;  /*modif taille groupe*/
			}
			else{
				if(tab_groupe[(courant->tab[3])-1]>= courant->taille){
					courant = courant->suivante;
					temp = suppression(&prec, tete);
					insertion(temp, &(tab_chaine[(temp->tab[3])-1])); 								/*Personne n'est dispo pour echanger*/
					temp->groupe = temp->tab[3];													/*Insertion du courant dans son voeux 4*/
					tab_groupe[(temp->tab[3])-1] = tab_groupe[(temp->tab[3])-1]-temp->taille;	/*Modif Taille groupe*/

				}
				else {
					prec = courant;
					courant = courant->suivante;
				}
			}
		}
	}
}
