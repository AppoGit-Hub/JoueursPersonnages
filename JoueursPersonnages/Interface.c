#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"

//les fonctions relatives au dialogue avec l’utilisateur, comme par 
//exemple l’affichage des divers menus, les obtentions d’informations(noms des
//personnages…) et l’affichage « en clair » des messages d’erreur renvoyés par les fonctions
//plus mécaniques(de Gestion et de Fichier par exemple)

//FonctionS pour afficher les choix qui s’offrent à l’utilisateur
//FonctionS de Gestion pour tout ce qui concerne la manipulation de la liste chaînée des joueurs en mémoire
//FonctionS de Fichier pour le chargement et la sauvegarde

void afficherMessage(Message* pLexique, int numMessage) {
	char* message;
	if (numMessage > 2000 && numMessage < 3000 ||
		numMessage > NUM_DEB_MESSAGE_ERREUR || 
		numMessage > 3400 && numMessage < NUM_DEB_MESSAGE_ERREUR) 
	{
		message = rechercheLexique(pLexique, numMessage);
		if (message) printf("%s", message);
	}
}

int afficherMenu(Message* pLexique, int debMenu) {
	for (int m = 0; m < 8; m++)
		printf("%s", rechercheLexique(pLexique, MENU_PRINCIPAL + m));
	return 8;
}

void afficherTitre(Message* pLexique, int numTitre) {
	if (numTitre < TITRE_PRINCIPAL || 
		numTitre > NUM_DEB_MESSAGE_ERREUR) return;
	char* titre = rechercheLexique(pLexique, numTitre);
	if (titre) printf("%s", titre);
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
				break;
			case AJOUTER_PERSONNAGE_PERSONNAGES:
				break;
			case SUPPRIMER_JOUEUR:
				break;
			case AFFICHER_JOUEURS_PERSONNAGES:
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
}

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

CodeErreur ajouterPersonnage(Message* pLexique, Joueur* pDebJoueurs) {
	Personnage* pNouvPerso;
	Joueur* pJoueur;
	Joueur* pSauvJoueur;
	bool alocationOk;
	char* pseudo;

	alocationOk = nouveauPersonnage(pNouvPerso);
	if (!alocationOk) return ALLOCATION_MEMOIRE;
	afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
	pseudo = pseudoObtenu(pLexique);
	
	alocationOk = joueurExiste(pDebJoueurs, pseudo, pJoueur, pSauvJoueur);
	if (!alocationOk) { liberePersonnage(pNouvPerso); return JOUEUR_ABSENT; }
	
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
		scanf("%s", &nom);
		estValide = !strcmp(&nom, "");
		if (!estValide) afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + NOM_NON_VALIDE);
	} while (!estValide);
	return nom;
}