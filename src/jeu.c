#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "jeu.h"
#include "suspect.h"
#include "ensemble.h"

/* #define DEBUG 1 Mettre à 1 pour affichages supplémentaires */
bool verbose = false;

void init_questions(struct question *questions);
void init_suspects (struct liste_suspects *ls);
char lecture_reponse(void);
void maj_suspects(struct liste_suspects *ls, uint8_t id, bool traitPresent);
void execution_jeu(struct liste_suspects *ls,
		   struct question *questions,
		   ensemble_t esuspect,
		   ensemble_t qPosees);
void libere_questions(struct question *questions);
void clear_input(void);

int
main(int argc, char **argv)
{
/* Affichage plus complet si "-v" en argument */
	if (argc == 2)
		if (!strcmp(argv[1], "-v"))
			verbose = true;

/* Initialisation des questions */
	srand (time(NULL)*time(NULL)); // Semble + aleatoire que time(NULL) seul
	struct question questions[NOMBRE_QUESTIONS];
	init_questions (questions);

/* Création de la liste des suspects
   et ajout des suspects dans la liste */
	struct liste_suspects *ls = creer_liste_suspects();
	init_suspects (ls);

/* Création d'un ensemble d'attributs vide afin de décrire le suspect */
	ensemble_t esuspect = ensemble_vide();
/* Ensemble pour marquer les questions déjà posées */
	ensemble_t qPosees = ensemble_vide();

/* Execution de la boucle de jeu principale */
	printf ("\t\t\t\033[32;1m== ENSIMAG Qui-est-ce ? ==\033[0m\n");
	printf ("Choisissez un personnage et répondez aux questions.\n");
	if (!verbose)
		printf ("Relancez avec l'argument \033[31;1m\"-v\"\033[0m pour"
			" un affichage plus complet.\n");
	printf ("\n");
	execution_jeu (ls, questions, esuspect, qPosees);

/* Liberation de la mémoire */
	libere_questions (questions);
	detruire_liste_suspects (&ls);

	return 0;
}

/* Initialise les questions et les stocke dans le tableau questions */
void
init_questions(struct question *questions)
{
	questions[0].str = "Le suspect est-il un homme ? [o/n]\n";
	questions[0].nb_qliees = 1;
	questions[0].qliees = malloc (questions[0].nb_qliees
				      * sizeof (uint8_t));
	questions[0].qliees[0] = 1;

	questions[1].str = "Le suspect est-il une femme ? [o/n]\n";
	questions[1].nb_qliees = 1;
	questions[1].qliees = malloc (questions[1].nb_qliees
				      * sizeof (uint8_t));
	questions[1].qliees[0] = 0;

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
}

/* Crée les suspects et les ajoute à la liste ls */
void
init_suspects (struct liste_suspects *ls)
{
	ajouter_suspect(ls, creer_suspect("André ", ANDRE));
	ajouter_suspect(ls, creer_suspect("Philippe", PHILIPPE));
	ajouter_suspect(ls, creer_suspect("Jean-Louis", JEAN_LOUIS));
	ajouter_suspect(ls, creer_suspect("François", FRANCOIS));
	ajouter_suspect(ls, creer_suspect("Robert", ROBERT));
	ajouter_suspect(ls, creer_suspect("Carole", CAROLE));
	ajouter_suspect(ls, creer_suspect("Mélanie", MELANIE));
	ajouter_suspect(ls, creer_suspect("Fabien", FABIEN));
	ajouter_suspect(ls, creer_suspect("Patricia", PATRICIA));
	ajouter_suspect(ls, creer_suspect("Baptiste", BAPTISTE));
	ajouter_suspect(ls, creer_suspect("Sébastien", SEBASTIEN));
	ajouter_suspect(ls, creer_suspect("Olivier", OLIVIER));
	ajouter_suspect(ls, creer_suspect("Nicolas", NICOLAS));
	ajouter_suspect(ls, creer_suspect("Luc   ", LUC));
	ajouter_suspect(ls, creer_suspect("Simon ", SIMON));
	ajouter_suspect(ls, creer_suspect("Maxime", MAXIME));
	ajouter_suspect(ls, creer_suspect("Cédric", CEDRIC));
	ajouter_suspect(ls, creer_suspect("Pierre", PIERRE));
	ajouter_suspect(ls, creer_suspect("Martin", MARTIN));
	ajouter_suspect(ls, creer_suspect("Elodie", ELODIE));
	ajouter_suspect(ls, creer_suspect("Victor", VICTOR));
	ajouter_suspect(ls, creer_suspect("Georges", GEORGES));
	ajouter_suspect(ls, creer_suspect("Thierry", THIERRY));
	ajouter_suspect(ls, creer_suspect("Céline", CELINE));
}

/* Récupère les entrées de stdin jusqu'au NewLine suivant.
   Permet d'éviter de répondre par erreur à plusieurs questions d'un coup */
void
clear_input (void)
{
	while (getchar () != '\n');
}

/* Boucle de jeu principale :
 * Tant qu'il reste des questions ou plus d'un suspect dans la liste,
 * boucle et pose les questions restantes.
 *
 * En sortie de la boucle, soit il reste un suspect et le jeu s'est bien
 * déroulé, soit il n'en reste aucun et le témoin a menti,
 * soit il n'en reste plusieurs et aucune question et le témoin a aussi menti
 */
void
execution_jeu(struct liste_suspects *ls,
	      struct question *questions,
	      ensemble_t esuspect,
	      ensemble_t qPosees)
{
	while ((ls->nb_suspects > 1)
	       && (ensemble_cardinal (qPosees)) < NOMBRE_QUESTIONS) {

		/* Tire un id de question aléatoirement */
		uint8_t id = rand() % NOMBRE_QUESTIONS;

		/* On la traite que si celle-ci n'a pas encore été posée */
		if (!ensemble_appartient (qPosees, id)) {
			/* Affichage et marquage de la question */
			printf (questions[id].str);
			ensemble_ajouter_elt(&qPosees, id);

			char ans = lecture_reponse ();

			/* Traitement de la réponse */
			if (ans == 'o') {
				ensemble_ajouter_elt(&esuspect, id);

				/* Marquage des questions liées comme à ne plus poser */
				for (uint8_t i = 0; i < questions[id].nb_qliees; i++) {
					ensemble_retirer_elt(&esuspect,
							     questions[id].qliees[i]);
					ensemble_ajouter_elt(&qPosees,
							     questions[id].qliees[i]);
				}

			        maj_suspects (ls, id, true);
			} else {
				ensemble_retirer_elt(&esuspect, id);
			        maj_suspects (ls, id, false);
			}

			if (verbose){
				ensemble_afficher ("suspect : ", esuspect);
				ensemble_afficher ("qPosees  : ", qPosees);
			}
		}
	}

/* Fin de partie */
	printf ("\n--> Partie terminée.\n");
	/* Si il reste un seul suspect, le résultat est correct */
	if (ls->nb_suspects == 1) {
		printf ("Le personnage que vous avez choisi est"
			" : \033[34;1m%s\033[0m\n", ls->tete->nom);
	} else { // sinon, le témoin a menti
		printf ("Personne ne correspond à la description.\n");
		printf ("Vous avez \033[31;1mMENTI\033[0m !\n");
		exit(1);
	}
}

/* Invite l'utilisateur à répondre à la question jusqu'à ce qu'il fournisse
   une réponse valide */
char
lecture_reponse(void) {
	char ans = '\0';
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

	return ans;
}


/* Met à jour la liste des suspects en fonction de la dernière question.
 * Si traitPresent vaut true, on ne garde que les suspects qui ont le
 * trait d'indice id.
 * Si il vaut false, on ne garde que ceux qui ne l'ont pas.
 */
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

	if (verbose)
		affiche_liste_suspects (ls);
}

/* Libere tous les tableaux de questions liées alloués */
void
libere_questions(struct question *questions)
{
	for (uint8_t i = 0; i < NOMBRE_QUESTIONS; i++) {
		free (questions[i].qliees);
	}
}
