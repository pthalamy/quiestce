#ifndef SUSPECT_H
#define SUSPECT_H

#include <stdlib.h>
#include <stdio.h>

#include "ensemble.h"

/* Suspect du jeu Qui est-ce. */
struct suspect {
        char *nom;
        ensemble_t attributs;
        struct suspect *suiv;
        struct suspect *prec;
};

/* Liste doublement chainée de suspects. */
struct liste_suspects {
        uint16_t nb_suspects;
        struct suspect *tete;
        struct suspect *queue;
};

/* Retourne un nouveau suspect initialisé en fonction des paramètres
 * nom et attributs. */
struct suspect *creer_suspect(const char *nom, ensemble_t attributs);

/* Créé une nouvelle liste de suspects, initialement vide. */
struct liste_suspects *creer_liste_suspects(void);

/* Détruit la liste de suspects passée en paramètre. */
void detruire_liste_suspects(struct liste_suspects **l);

/* Ajoute le suspect s en fin de la liste de suspects l. */
void ajouter_suspect(struct liste_suspects *l, struct suspect *s);

/* Retire le suspect s de la liste de suspects l. */
void retirer_suspect(struct liste_suspects *l, struct suspect *s);

/* Affiche les noms de tous les suspects de la liste l. */
void affiche_liste_suspects(struct liste_suspects *l);

/* Genre */
#define HOMME             0b0000000000000001
#define FEMME             0b0000000000000010
/* Pilosité */
#define MOUSTACHE         0b0000000000000100
#define BARBE             0b0000000000001000
/* Coiffure */
#define COIFFURE_CHAUVE   0b0000000000010000
#define COIFFURE_LONG     0b0000000000100000
#define COIFFURE_COURT    0b0000000001000000
/* Couleur cheveux */
#define CHEVEUX_NOIRS     0b0000000010000000
#define CHEVEUX_CHATAINS  0b0000000100000000
#define CHEVEUX_BLANCS    0b0000001000000000
#define CHEVEUX_ROUX      0b0000010000000000
#define CHEVEUX_BLONDS    0b0000100000000000
/* Accessoires */
#define LUNETTES          0b0001000000000000
#define CHAPEAU           0b0010000000000000

#endif /* SUSPECT_H */
