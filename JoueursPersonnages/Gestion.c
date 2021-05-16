#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"

//les fonctions liées aux listes chaînées retenues en mémoire et stockant les joueurs et leurs personnages
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

bool nouveauJoueur(Joueur* pNouvJoueur) {
	pNouvJoueur = (Joueur*)malloc(sizeof(Joueur));
	return pNouvJoueur != NULL;
}

void ajouteJoueur(
	Joueur* pDebJoueurs,
	char pseudo[TPSEUDO],
	Joueur* pNouvJoueur,
	Joueur* pJoueur,
	Joueur* pSauvJoueur) {
	
	pNouvJoueur->pseudo = pseudo;
	pNouvJoueur->pDebPersonnages = NULL;
	if (pJoueur == pDebJoueurs) pDebJoueurs = pNouvJoueur;
	else pSauvJoueur->pSuiv = pNouvJoueur;
	pNouvJoueur->pSuiv = pJoueur;
}

bool nouveauPersonnage(Personnage* pNouvPerso) {
	pNouvPerso = (Personnage*)malloc(sizeof(Personnage));
	return pNouvPerso != NULL;
}

void ajoutePersonnage(Joueur* pJoueur, char nom[TNOM], int xp, Personnage* pNouvPerso) {
	pNouvPerso->nom = nom;
	pNouvPerso->xp = xp;
	pNouvPerso->pSuiv = pJoueur->pDebPersonnages;

	pJoueur->pDebPersonnages = pNouvPerso;
}