#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"


void main(void) {
	Message* pLexique = NULL;
	CodeErreur erreurLexique = chargerLexique(&pLexique);
	
	/*
	Message* pMenu = pLexique;
	while (pMenu != NULL) {
		printf("%d - %s\n", pMenu->numero, pMenu->message);
		pMenu = pMenu->pSuiv;
	}
	*/

	switch (erreurLexique)
	{
		case PAS_D_ERREUR:
			dialogue(pLexique);
			libererLexique(pLexique);
			break;
		case ALLOCATION_MEMOIRE:
			printf("ALLOCATION_MEMOIRE");
			libererLexique(pLexique);
			break;
		case FICHIER_INEXISTANT:
			break;
		default:
			break;
	}
}