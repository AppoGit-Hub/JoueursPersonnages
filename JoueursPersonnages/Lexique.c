#include "Constantes.h"
#include "Lexique.h"

void libererLexique(Message* pLexique) {
	if (pLexique == NULL) { return; }
	libererLexique(pLexique->pSuiv);
	free(pLexique);
}
