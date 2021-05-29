#include "Constantes.h"
#include "Lexique.h"
#include "JoueursPersonnages.h"


void main(void) {
	Message* pLexique = NULL;
	CodeErreur erreurLexique = chargerLexique(&pLexique);
	
	switch (erreurLexique)
	{
		case PAS_D_ERREUR:
			dialogue(pLexique);
		case ALLOCATION_MEMOIRE:
		case FICHIER_INEXISTANT:
			libererLexique(pLexique);
			break;
		default:
			break;
	}
}