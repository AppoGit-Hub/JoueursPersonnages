#ifndef JOUEURSPERSONNAGES_H
#define JOUEURSPERSONNAGES_H
	#include "Constantes.h"

	typedef struct personnage Personnage;
	struct personnage {
		char* nom;
		int xp;
		Personnage* pSuiv;
	};

	typedef struct joueur Joueur;
	struct joueur {
		char* pseudo;
		Personnage* pDebPersonnages;
		int nbPerso;
		Joueur* pSuiv;
	};

	CodeErreur fichierExiste();
	void libereJoueursPersonnages(Joueur* pDebJoueurs);
	CodeErreur chargerJoueurs(Joueur* pDebJoueurs);
	bool nouveauJoueur(Joueur* pNouvJoueur);
	void ajouteJoueur(Joueur* pDebJoueurs, char pseudo[TPSEUDO], Joueur* pNouvJoueur, Joueur* pJoueur, Joueur* pSauvJoueur);
	bool nouveauPersonnage(Personnage* pNouvPerso);
	void ajoutePersonnage(Joueur* pJoueur, char nom[TNOM], int xp, Personnage* pNouvPerso);
#endif 

