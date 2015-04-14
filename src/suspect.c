#include "suspect.h"

struct suspect *creer_suspect(const char *name, ensemble_t attributs) {
  if (name != NULL) {
    struct suspect *s = malloc (sizeof(struct suspect));
    s->nom = (char*)name;

    s->attributs = attributs;
    s->prec = NULL;
    s->suiv = NULL;

    return s;
  } else {
    return NULL;
  }
}

struct liste_suspects *creer_liste_suspects(void) {
  struct liste_suspects *ls = malloc (sizeof(struct liste_suspects));
  ls->nb_suspects = 0;
  ls->tete = NULL;
  ls->queue = NULL;

  return ls;
}

void detruire_liste_suspects(struct liste_suspects **l) {
  struct suspect *scour = (*l)->tete;
  struct suspect *ssuiv;

  while (scour != NULL) {
    ssuiv = scour->suiv;
    retirer_suspect (*l, scour);
    scour = ssuiv;
  }

  free (*l);
}

void ajouter_suspect(struct liste_suspects *liste, struct suspect *suspect) {
  if (liste->tete == NULL) {
    liste->tete = liste->queue = suspect;
  } else {
    liste->queue->suiv = suspect;
    suspect->prec = liste->queue;
    liste->queue = suspect;
  }

  liste->nb_suspects++;
}

void retirer_suspect(struct liste_suspects *liste, struct suspect *suspect) {
  if (suspect != liste->tete)
    suspect->prec->suiv = suspect->suiv;
  else
    liste->tete = suspect->suiv;

  if (suspect != liste->queue)
    suspect->suiv->prec = suspect->prec;
  else
    liste->queue = suspect->prec;

  free (suspect);
  liste->nb_suspects--;
}

void affiche_liste_suspects(struct liste_suspects *l) {
  printf ("NULL ");

  for (struct suspect *scour = l->tete;
       scour != NULL;
       scour = scour->suiv) {
    printf ("-> Nom : %s – attributs : %x ", scour->nom, scour->attributs);
  }

  printf ("-> NULL\n");
}
