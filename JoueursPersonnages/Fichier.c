#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"

//les fonctions li�es � l�utilisation du fichier de donn�es des joueurs et de leurs personnages; 
//entre autres, la sauvegarde et le chargement des donn�es.

//NOTE: s'occupe de la lecture et de l'�criture. Si manip liste->demande a Gestion.c

CodeErreur chargerLexique(Message** pPLexique) {
	FILE* pFIFrancais;

	fopen_s(&pFIFrancais, FIFRANCAIS, "r");
	if (pFIFrancais == NULL) return FICHIER_INEXISTANT;
	
	Message* pMessage = *pPLexique;
	Message* pNouvMessage;
	char message[TTXT];

	while (!feof(pFIFrancais))
	{
		pNouvMessage = (Message*)malloc(sizeof(Message));
		if (pNouvMessage == NULL) return ALLOCATION_MEMOIRE;

		fscanf_s(pFIFrancais, "%d ", &pNouvMessage->numero);
		fgets(&message, TTXT, pFIFrancais);

		strcpy_s(pNouvMessage->message, TTXT, message);
		pNouvMessage->pSuiv = NULL;

		if (*pPLexique == NULL) { *pPLexique = pNouvMessage; }
		else { pMessage->pSuiv = pNouvMessage; }
		pMessage = pNouvMessage;
	}

	fclose(pFIFrancais);
	return PAS_D_ERREUR;
}

CodeErreur fichierExiste() {
	FILE* pFIJoueurs;
	fopen_s(&pFIJoueurs, FIJOUEURS, "rb");
	if (pFIJoueurs == NULL) return FICHIER_INEXISTANT;
	fclose(pFIJoueurs);
	return PAS_D_ERREUR;
}

CodeErreur chargerJoueurs(Joueur* pDebJoueurs) {
	FILE* pFIJoueurs;

	fopen_s(&pFIJoueurs, FIJOUEURS, "rb");
	if (pFIJoueurs == NULL) return FICHIER_INEXISTANT;

	Joueur* pJoueur;
	Joueur* pNouvJoueur;
	Joueur* pSauvJoueur;
	bool alocationOk;
	int iPersonnage;

	Personnage* pNouvPerso = NULL;

	fread_s(&pJoueur, sizeof(Joueur), sizeof(Joueur), 1, pFIJoueurs);
	while (!feof(pFIJoueurs))
	{
		alocationOk = nouveauJoueur(&pNouvJoueur);
		if (!alocationOk) return ALLOCATION_MEMOIRE;

		ajouteJoueur(pDebJoueurs, pJoueur->pseudo, pNouvJoueur, pJoueur, &pSauvJoueur);
		pSauvJoueur = pNouvJoueur;

		iPersonnage = 0;
		while (iPersonnage < pJoueur->nbPerso && alocationOk)
		{
			alocationOk = nouveauPersonnage(pNouvPerso);
			if (!alocationOk) return ALLOCATION_MEMOIRE;

			fread_s(&pNouvPerso, sizeof(Personnage), sizeof(Personnage), 1, pFIJoueurs);
			ajoutePersonnage(&pJoueur, &pNouvPerso->nom, &pNouvPerso->xp, &pNouvPerso);
			iPersonnage++;
		}
		if (alocationOk) fread_s(pJoueur, sizeof(Joueur), sizeof(Joueur), 1, pFIJoueurs);
	}
	fclose(pFIJoueurs);
}