#include <stdlib.h>
#include <time.h>

#include "jeu.h"
#include "suspect.h"
#include "ensemble.h"

void init_questions(struct question *questions);
void init_suspects (struct liste_suspects *ls);
void maj_suspects(struct liste_suspects *ls, uint8_t id, bool traitPresent);
void execution_jeu(struct liste_suspects *ls,
		   struct question *questions,
		   ensemble_t esuspect);
void libere_questions (struct question *questions);
void clear(void);

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

/* Création d'un ensemble d'attributs vide afin de décrire le suspect */
	ensemble_t esuspect = ensemble_vide();

/* Execution de la boucle de jeu principale */
	printf ("\t\t\t\033[32;1m== ENSIMAG Qui-est-ce ? ==\033[0m\n");
	printf ("Choisissez un personnage et répondez aux questions.\n\n");
	execution_jeu (ls, questions, esuspect);

/* Fin de partie */
	printf ("\n--> Partie terminée.\n");
	if (ls->nb_suspects == 1) {
		printf ("Le personnage que vous avez choisi est : \033[34;1m%s\033[0m\n"
			, ls->tete->nom);
	} else {
		printf ("Personne ne correspond à la description.\n");
		printf ("Vous avez \033[31;1mMENTI\033[0m !\n");
		return 1;
	}

/* Liberation de la mémoire */
	libere_questions (questions);
	detruire_liste_suspects (&ls);

	return 0;
}

void
init_questions(struct question *questions)
{
	questions[0].str = "Le suspect est-il un homme ? [o/n]\n";
	questions[0].nb_qliees = 0;

	questions[1].str = "Le suspect est-il une femme ? [o/n]\n";
	questions[1].nb_qliees = 0;

	questions[2].str = "Le suspect a-t-il une moustache ? [o/n]\n";
	questions[2].nb_qliees = 0;
	questions[2].qliees = NULL;

	questions[3].str = "Le suspect a-t-il une barbe ? [o/n]\n";
	questions[3].nb_qliees = 0;
	questions[3].qliees = NULL;

	questions[4].str = "Le suspect est-il chauve ? [o/n]\n";
	questions[4].nb_qliees = 2;
	questions[4].qliees = malloc (questions[4].nb_qliees
				      * sizeof (uint8_t));
	questions[4].qliees[0] = 5;
	questions[4].qliees[1] = 6;

	questions[5].str = "Le suspect a-t-il les cheveux longs ? [o/n]\n";
	questions[5].nb_qliees = 2;
	questions[5].qliees = malloc (questions[5].nb_qliees
				      * sizeof (uint8_t));
	questions[5].qliees[0] = 4;
	questions[5].qliees[1] = 6;

	questions[6].str = "Le suspect a-t-il des cheveux courts ? [o/n]\n";
	questions[6].nb_qliees = 2;
	questions[6].qliees = malloc (questions[6].nb_qliees
				      * sizeof (uint8_t));
	questions[6].qliees[0] = 4;
	questions[6].qliees[1] = 5;

	questions[7].str = "Le suspect a-t-il les cheveux noirs ? [o/n]\n";
	questions[7].nb_qliees = 4;
	questions[7].qliees = malloc (questions[7].nb_qliees
				      * sizeof (uint8_t));
	questions[7].qliees[0] = 8;
	questions[7].qliees[1] = 9;
	questions[7].qliees[2] = 10;
	questions[7].qliees[3] = 11;

	questions[8].str = "Le suspect a-t-il les cheveux chatains"
		" / bruns ? [o/n]\n";
	questions[8].nb_qliees = 4;
	questions[8].qliees = malloc (questions[8].nb_qliees
				      * sizeof (uint8_t));
	questions[8].qliees[0] = 7;
	questions[8].qliees[1] = 9;
	questions[8].qliees[2] = 10;
	questions[8].qliees[3] = 11;


	questions[9].str = "Le suspect a-t-il les cheveux blancs ? [o/n]\n";
	questions[9].nb_qliees = 4;
	questions[9].qliees = malloc (questions[9].nb_qliees
				      * sizeof (uint8_t));
	questions[9].qliees[0] = 7;
	questions[9].qliees[1] = 8;
	questions[9].qliees[2] = 10;
	questions[9].qliees[3] = 11;

	questions[10].str = "Le suspect a-t-il les cheveux roux ? [o/n]\n";
	questions[10].nb_qliees = 4;
	questions[10].qliees = malloc (questions[10].nb_qliees
				       * sizeof (uint8_t));
	questions[10].qliees[0] = 7;
	questions[10].qliees[1] = 8;
	questions[10].qliees[2] = 9;
	questions[10].qliees[3] = 11;

	questions[11].str = "Le suspect a-t-il les cheveux blonds ? [o/n]\n";
	questions[11].nb_qliees = 4;
	questions[11].qliees = malloc (questions[11].nb_qliees
				       * sizeof (uint8_t));
	questions[11].qliees[0] = 7;
	questions[11].qliees[1] = 8;
	questions[11].qliees[2] = 9;
	questions[11].qliees[3] = 10;

	questions[12].str = "Le suspect a-t-il des lunettes ? [o/n]\n";
	questions[12].nb_qliees = 0;
	questions[12].qliees = NULL;

	questions[13].str = "Le suspect a-t-il un chapeau ? [o/n]\n";
	questions[13].nb_qliees = 0;
	questions[13].qliees = NULL;

	for (uint8_t i = 0; i < NOMBRE_QUESTIONS; i++)
	        questions[i].toAsk = true;
}

void
init_suspects (struct liste_suspects *ls)
{
	struct suspect *suspects[NOMBRE_SUSPECTS];

	suspects[0] = creer_suspect("André ", ANDRE);
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
	suspects[13] = creer_suspect("Luc   ", LUC);
	suspects[14] = creer_suspect("Simon ", SIMON);
	suspects[15] = creer_suspect("Maxime", MAXIME);
	suspects[16] = creer_suspect("Cédric", CEDRIC);
	suspects[17] = creer_suspect("Pierre", PIERRE);
	suspects[18] = creer_suspect("Martin", MARTIN);
	suspects[19] = creer_suspect("Elodie", ELODIE);
	suspects[20] = creer_suspect("Victor", VICTOR);
	suspects[21] = creer_suspect("Georges", GEORGES);
	suspects[22] = creer_suspect("Thierry", THIERRY);
	suspects[23] = creer_suspect("Céline", CELINE);

	for (uint8_t i = 0; i < NOMBRE_SUSPECTS; i++)
	        ajouter_suspect(ls, suspects[i]);
}

void
clear_input (void)
{
	while (getchar () != '\n');
}

void
execution_jeu(struct liste_suspects *ls,
	      struct question *questions,
	      ensemble_t esuspect)
{
	while ((ls->nb_suspects > 1) && (qrestantes(questions) > 0)) {
		uint8_t id = rand() % NOMBRE_QUESTIONS;
		if (questions[id].toAsk) {
			printf (questions[id].str);
			questions[id].toAsk = false;

			char ans = '0';
			while ((ans != 'o') && (ans != 'n')) {
				scanf ("%c", &ans);

				if ((ans != 'o') && (ans != 'n')
				    && (ans != '\n')) {
					fprintf (stderr,
						 "Répondez par (o)ui"
						 " ou (n)on !\n");
				}

				clear_input();
			}

			if (ans == 'o') {
				ensemble_ajouter_elt(&esuspect, id);

				if (id == 0) {
					questions[1].toAsk = false;
					ensemble_retirer_elt(&esuspect, 1);
				} else if (id == 1) {
					questions[0].toAsk = false;
					ensemble_retirer_elt(&esuspect, 0);
				}

				for (uint8_t i = 0; i < questions[id].nb_qliees; i++) {
					questions[questions[id].qliees[i]].toAsk
						= false;
				}

			        maj_suspects (ls, id, true);
			} else {
				ensemble_retirer_elt(&esuspect, id);

				if (id == 0) {
					questions[1].toAsk = false;
					ensemble_ajouter_elt(&esuspect, 1);
				} else if (id == 1) {
					questions[0].toAsk = false;
					ensemble_ajouter_elt(&esuspect, 0);
				}

				for (uint8_t i = 0;
				     i < questions[id].nb_qliees;
				     i++) {
					ensemble_retirer_elt(
						&esuspect,
					        questions[id].qliees[i]);
				}

			        maj_suspects (ls, id, false);
			}

			/* DEBUG */
			/* ensemble_afficher ("suspect : ", esuspect); */
		}
	}
}

void
maj_suspects(struct liste_suspects *ls, uint8_t id, bool traitPresent)
{
	/* Mise à jour de la liste */
	struct suspect *scour = ls->tete;
	struct suspect *ssuiv;

	while (scour != NULL) {
		ssuiv = scour->suiv;
		if ((traitPresent) ^ (ensemble_appartient
				      (scour->attributs, id))) {
			retirer_suspect (ls, scour);
		}
		scour = ssuiv;
	}

	/* DEBUG */
	/* affiche_liste_suspects (ls); */
}

uint8_t
qrestantes(const struct question *questions)
{
        uint8_t count = 0;
	for (uint8_t i = 0; i < NOMBRE_QUESTIONS; i++)
		if (questions[i].toAsk)
			count++;

	return count;
}

void
libere_questions (struct question *questions)
{
	for (uint8_t i = 0; i < NOMBRE_QUESTIONS; i++) {
		free (questions[i].qliees);
	}
}
