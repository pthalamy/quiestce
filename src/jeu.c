#include <stdlib.h>
#include <time.h>

#include "jeu.h"
#include "suspect.h"
#include "ensemble.h"

void init_questions(struct question *questions);
void init_suspects (struct liste_suspects *ls);

int main(void)
{

/* Initialisation des questions */
	srand (time(NULL));
	struct question questions[NOMBRE_QUESTIONS];
	init_questions (questions);


/* Création de la liste des suspects
   et ajout des suspects dans la liste */
	struct liste_suspects *ls = creer_liste_suspects();
	init_suspects (ls);

	affiche_liste_suspects (ls);

/* Liberation de la mémoire */
	detruire_liste_suspects (&ls);

	return 0;
}

void init_questions(struct question *questions)
{
	questions[0].str = "Le suspect est-il un homme ?";
	questions[1].str = "Le suspect est-il une femme ?";
	questions[2].str = "Le suspect a-t-il une moustache ?";
	questions[3].str = "Le suspect a-t-il une barbe ?";
	questions[4].str = "Le suspect est-il chauve ?";
	questions[5].str = "Le suspect a-t-il de long cheveux ?";
	questions[6].str = "Le suspect a-t-il des cheveux courts ?";
	questions[7].str = "Le suspect a-t-il les cheveux noirs ?";
	questions[8].str = "Le suspect a-t-il les cheveux chatains / bruns ?";
	questions[9].str = "Le suspect a-t-il les cheveux blancs ?";
	questions[10].str = "Le suspect a-t-il les cheveux roux ?";
	questions[11].str = "Le suspect a-t-il les cheveux blonds ?";
	questions[12].str = "Le suspect a-t-il des lunettes ?";
	questions[13].str = "Le suspect a-t-il un chapeau ?";

	for (uint8_t i = 0; i < NOMBRE_QUESTIONS; i++)
	        questions[i].toAsk = true;
}

void init_suspects (struct liste_suspects *ls)
{
	struct suspect *suspects[NOMBRE_SUSPECTS];

	suspects[0] = creer_suspect("André", ANDRE);
	suspects[1] = creer_suspect("Philippe", PHILIPPE);
	suspects[2] = creer_suspect("Jean-Louis", JEAN_LOUIS);
	suspects[3] = creer_suspect("François", FRANCOIS);
	suspects[4] = creer_suspect("Robert", ROBERT);
	suspects[5] = creer_suspect("Carole", CAROLE);
	suspects[6] = creer_suspect("Mélanie", MELANIE);
	suspects[7] = creer_suspect("Fabien", FABIEN);
	suspects[8] = creer_suspect("Patricia", PATRICIA);
	suspects[9] = creer_suspect("Baptiste", BAPTISTE);
	suspects[10] = creer_suspect("Sébastien", SEBASTIEN);
	suspects[11] = creer_suspect("Olivier", OLIVIER);
	suspects[12] = creer_suspect("Nicolas", NICOLAS);
	suspects[13] = creer_suspect("Luc", LUC);
	suspects[14] = creer_suspect("Simon", SIMON);
	suspects[15] = creer_suspect("Maxime", MAXIME);
	suspects[16] = creer_suspect("Cédric", CEDRIC);
	suspects[17] = creer_suspect("Pierre", PIERRE);
	suspects[18] = creer_suspect("Martin", MARTIN);
	suspects[19] = creer_suspect("Elodie", MAXIME);
	suspects[20] = creer_suspect("Victor", VICTOR);
	suspects[21] = creer_suspect("Georges", GEORGES);
	suspects[22] = creer_suspect("Thierry", THIERRY);
	suspects[23] = creer_suspect("Céline", CELINE);

	for (uint8_t i = 0; i < NOMBRE_SUSPECTS; i++)
	        ajouter_suspect(ls, suspects[i]);
}
