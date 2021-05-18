#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"

//les fonctions li�es aux listes cha�n�es retenues en m�moire et stockant les joueurs et leurs personnages
//NOTE: ne communique directement pas avec le joueur et renvoir des code erreur

char* rechercheLexique(Message* pLexique, int id) {
	Message* pDebut = pLexique;
	while (pDebut != NULL && pDebut->numero != id) {
		pDebut = pDebut->pSuiv;
	}
	if (pDebut == NULL) return NULL;
	return pDebut->message;
}

void libereJoueursPersonnages(Joueur* pDebJoueurs) {
	if (pDebJoueurs == NULL) { return; }
	libererLexique(pDebJoueurs->pSuiv);
	free(pDebJoueurs);
}

void liberePersonnage(Personnage* pPersonnage) {
	free(pPersonnage);
}

void libererJoueur(Joueur* pJoueur) {
	free(pJoueur);
}
bool nouveauJoueur(Joueur** pNouvJoueur) {
	*pNouvJoueur = (Joueur*)malloc(sizeof(Joueur));
	return *pNouvJoueur != NULL;
}

bool joueurExiste(
	Joueur* pDebJoueurs, 
	char pseudo[TPSEUDO], 
	Joueur* pJoueur, 
	Joueur* pSauvJoueur) {
	pJoueur = pDebJoueurs;
	while (pJoueur != NULL && pseudo < pJoueur->pseudo)
	{
		pSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	return pJoueur != NULL && pseudo == pJoueur->pseudo;
}

bool personnageExiste(Joueur* pDebJoueurs, char nom[TNOM]) {
	Joueur* pJoueur = pDebJoueurs;
	Joueur* pPerso = NULL;
	bool existe = false;
	while (pJoueur != NULL && !existe)
	{
		pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL && strcmp(nom, pPerso->pseudo) == 0)
		{
			pPerso = pPerso->pSuiv;
		}
		existe = pPerso != NULL && strcmp(nom, pPerso->pseudo) == 0;
		pJoueur = pJoueur->pSuiv;
	}
}

void ajouteJoueur(Joueur* pDebJoueurs, char pseudo[TPSEUDO], Joueur* pNouvJoueur, Joueur* pJoueur, Joueur* pSauvJoueur) {
	pNouvJoueur->pseudo = pseudo;
	pNouvJoueur->pDebPersonnages = NULL;
	if (pJoueur == pDebJoueurs) pDebJoueurs = pNouvJoueur;
	else pSauvJoueur->pSuiv = pNouvJoueur;
	pNouvJoueur->pSuiv = pJoueur;
}

void supprimeJoueur(
	Joueur* pDebJoueurs, 
	Joueur* pJoueur,
	Joueur* pSauvJoueur) {
	Personnage* pPerso = pJoueur->pDebPersonnages;
	Personnage* pSauvPerso;
	while (pPerso != NULL)
	{
		pSauvPerso = pPerso->pSuiv;
		liberePersonnage(pPerso);
		pPerso = pSauvPerso;
	}
	if (pJoueur = pDebJoueurs) { pDebJoueurs = pJoueur->pSuiv; }
	else { pSauvJoueur->pSuiv = pJoueur->pSuiv; }
	libererJoueur(pJoueur);
}

CodeErreur ajouterPersonnageAJoueur(
	Message* pLexique, 
	Joueur* pDebJoueurs, 
	Joueur* pJoueur, 
	Personnage* pNouvPerso) {
	char* nom = nomObtenu(pLexique);
	bool persoExiste = personnageExiste(pDebJoueurs, nom);
	if (persoExiste) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PERSONNAGE_DEJA_PRESENT);
		liberePersonnage(pNouvPerso);
	}
	else {
		if (nbPersonnages(pJoueur) == NBMAXPERSO) return NB_MAX_PERSO_ATTEINT;
		ajoutePersonnage(pJoueur, &nom, pointsObtenu(pLexique), pNouvPerso);
	}
	return PAS_D_ERREUR;
}

bool nouveauPersonnage(Personnage** pNouvPerso) {
	*pNouvPerso = (Personnage*)malloc(sizeof(Personnage));
	return *pNouvPerso != NULL;
}

void ajoutePersonnage(Joueur* pJoueur, char nom[TNOM], int xp, Personnage* pNouvPerso) {
	pNouvPerso->nom = nom;
	pNouvPerso->xp = xp;
	pNouvPerso->pSuiv = pJoueur->pDebPersonnages;

	pJoueur->pDebPersonnages = pNouvPerso;
}

int nbPersonnages(Joueur* pJoueur) {
	Joueur* pDebut = pJoueur;
	int nombre = 0;
	while (pDebut != NULL)
	{
		pDebut = pDebut->pSuiv;
		nombre++;
	}
	return nombre;
}
