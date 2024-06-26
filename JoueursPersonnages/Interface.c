#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"

//les fonctions relatives au dialogue avec l�utilisateur, comme par 
//exemple l�affichage des divers menus, les obtentions d�informations(noms des
//personnages�) et l�affichage � en clair � des messages d�erreur renvoy�s par les fonctions
//plus m�caniques(de Gestion et de Fichier par exemple)

//FonctionS pour afficher les choix qui s�offrent � l�utilisateur
//FonctionS de Gestion pour tout ce qui concerne la manipulation de la liste cha�n�e des joueurs en m�moire
//FonctionS de Fichier pour le chargement et la sauvegarde

ChoixMenu choixObtenu(Message* pLexique, int numMenu) {
	int maxChoix;
	int choix;
	bool choixValide;
	do {
		maxChoix = afficherMenu(pLexique, numMenu);
		afficherMessage(pLexique, OBT_CHOIX);
		scanf_s("%d", &choix);
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX);
	} while (!choixValide);
	return (ChoixMenu)choix;
}


CodeErreur chargerJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	CodeErreur codeErreur = fichierExiste();
	if (codeErreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if (pDebJoueurs != NULL) {
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			if (reponseObtenue(pLexique, OBT_CONTINUER) == OUI) {
				libereJoueursPersonnages(pDebJoueurs);
				codeErreur = chargerJoueurs(pDebJoueurs);
			}
		}
		else {
			codeErreur = chargerJoueurs(pDebJoueurs);
		}
	}
	return codeErreur;
}

void dialogue(Message* pLexique) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	Joueur* pDebJoueurs = NULL;
	ChoixMenu choix;

	choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	while (choix != QUITTER)
	{
		switch (choix)
		{
			case CHARGER_JOUEURS_PERSONNAGES:
				chargerJoueursPersonnages(pLexique, pDebJoueurs);
				break;
			case AJOUTER_JOUEUR_PERSONNAGES:
				ajouterJoueurPersonnages(pLexique, pDebJoueurs);
;				break;
			case AJOUTER_PERSONNAGE_PERSONNAGES:
				ajouterPersonnage(pLexique, pDebJoueurs);
				break;
			case SUPPRIMER_JOUEUR:
				supprimerJoueurPersonnages(pLexique, pDebJoueurs);
				break;
			case AFFICHER_JOUEURS_PERSONNAGES:
				afficherJoueursPersonnages(pLexique, pDebJoueurs);
				break;
			case SAUVER_JOUEURS_PERSONNAGES:
				break;
		}
		if (choix != PAS_D_ERREUR) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + codeErreur);
			codeErreur = PAS_D_ERREUR;
		}
		choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	}
	libereJoueursPersonnages(pDebJoueurs);
}


CodeErreur ajouterPersonnage(Message* pLexique, Joueur* pDebJoueurs) {
	Personnage* pNouvPerso = NULL;
	Joueur* pJoueur = NULL;
	Joueur* pSauvJoueur = NULL;
	bool alocationOk;
	char* pseudo;

	alocationOk = nouveauPersonnage(pNouvPerso);
	if (!alocationOk) return ALLOCATION_MEMOIRE;
	afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
	pseudo = pseudoObtenu(pLexique);
	
	alocationOk = joueurExiste(pDebJoueurs, pseudo, pJoueur, pSauvJoueur);
	if (!alocationOk) { liberePersonnage(pNouvPerso); return JOUEUR_ABSENT; }
	
	ajouterPersonnageAJoueur(pLexique, pDebJoueurs, pJoueur, pNouvPerso);
	return PAS_D_ERREUR;
}

char* pseudoObtenu(Message* pLexique) {
	char pseudo[TPSEUDO];
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		gets_s(&pseudo, TPSEUDO);
		pseudoValide = strlen(&pseudo) > 0 && isupper(pseudo[0]);
		if (!pseudoValide) afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE);
	} while (!pseudoValide);
	return pseudo;
}

int reponseObtenue(Message* pLexique, int numMessage) {
	int reponse = NON;
	if (numMessage == OBT_CONTINUER || numMessage == OBT_ENCORE) {
		printf("%s", rechercheLexique(pLexique, numMessage));
		scanf_s("%d", &reponse);
	}
	return reponse;
}

char* nomObtenu(Message* pLexique) {
	char nom[TNOM];
	bool estValide;
	do {
		afficherMessage(pLexique, OBT_NOM);
		scanf_s("%s", &nom, TNOM);
		estValide = strcmp(&nom, "") != 0;
		if (!estValide) afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + NOM_NON_VALIDE);
	} while (!estValide);
	return nom;
}

int pointsObtenu(Message* pLexique) {
	int points;
	bool estValide;
	do {
		afficherMessage(pLexique, OBT_POINTS);
		scanf_s("%d", &points);
		estValide = points > 0 && points < 1000;
		if (!estValide) afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + POINTS_NON_VALIDES);
	} while (!estValide);
	return points;
}

CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	Joueur* pNouvJoueur = NULL;
	
	bool allocationOk = nouveauJoueur(&pNouvJoueur);
	if (!allocationOk) return ALLOCATION_MEMOIRE;
	
	afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
	char* pseudo = pseudoObtenu(pLexique);
	Joueur* pJoueur = NULL;
	Joueur* pSauvJoueur = NULL;
	
	bool existe = joueurExiste(pDebJoueurs, pseudo, pJoueur, pSauvJoueur);
	if (existe) { libererJoueur(pNouvJoueur); return JOUEUR_DEJA_PRESENT; }

	ajouteJoueur(pDebJoueurs, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);
	Personnage** pNouvPerso = NULL;
	
	CodeErreur codeErreur;
	int reponse;
	do {
		allocationOk = nouveauPersonnage(&pNouvPerso);
		if (!allocationOk) return ALLOCATION_MEMOIRE;
		
		codeErreur = ajouterPersonnageAJoueur(pLexique, pDebJoueurs, pNouvJoueur, pNouvPerso);
		if (codeErreur != PAS_D_ERREUR) return codeErreur;
		
		reponse = reponseObtenue(pLexique, OBT_ENCORE); 
	} while (allocationOk && codeErreur == PAS_D_ERREUR && reponse == OUI);
	return PAS_D_ERREUR;
}


CodeErreur supprimerJoueurPersonnages(Message* pLexique, Joueur* pDebJoueur) {
	Joueur* pJoueur = NULL;
	Joueur* pSauvJoueur = NULL;
	char* pseudo;
	bool SiJoueurExiste;

	afficherTitre(pLexique, TITRE_JOUEUR_ANNUL);
	pseudo = pseudoObtenu(pLexique);
	SiJoueurExiste = joueurExiste(pDebJoueur, pseudo, pJoueur, pSauvJoueur);
	if (!SiJoueurExiste) return JOUEUR_ABSENT;
	else supprimeJoueur(pDebJoueur, pJoueur, pSauvJoueur);

	return PAS_D_ERREUR;
}

void listeJoueurs(Joueur* pDebJoueurs) {
	Joueur* pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		printf("%s", pJoueur->pseudo);
		pJoueur = pJoueur->pSuiv;
	}
}

void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	if (pDebJoueurs == NULL) afficherMessage(pLexique, AUCUN_JOUEUR);
	else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueurs(pDebJoueurs);
	}
}

CodeErreur sauverJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	if (pDebJoueurs == NULL) afficherMessage(pLexique, AUCUN_JOUEUR);
	else {
		afficherTitre(pLexique, SAUVEGARDE);
		codeErreur = sauverJoueurs(pDebJoueurs);
	}
}
