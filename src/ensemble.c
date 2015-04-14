#include "ensemble.h"

#define BIT(e, n) ((e >> n) & 1)
#define SET_BIT(e, n) (e |= 1 << n)
#define CLEAR_BIT(e, n) (e &= ~(1 << n))

ensemble_t ensemble_vide(void) {
    return 0x0; // 16 bits à 0
}

ensemble_t ensemble_plein(void) {
    return 0xFFFF; // 16 bits à 1
}

uint16_t ensemble_cardinal(ensemble_t e) {
    uint16_t count = 0;
    uint16_t mask = 0x1;

    for (uint8_t i = 0; i < 16; i++, mask*2) {
    	if (BIT(e, i) == mask)
	    count++;
    }

    return count;
}

bool ensemble_appartient(ensemble_t e, uint16_t numero_elt) {
    return BIT(e, numero_elt);
}

ensemble_t ensemble_union(ensemble_t e1, ensemble_t e2) {
    uint16_t mask = 0x1;
    ensemble_t eu = 0x0;


    for (uint8_t i = 0; i < 16; i++, mask*2) {
    	if (BIT(e1, i) | BIT(e2, i))
	    SET_BIT (eu, i);
    }

    return eu;
}

ensemble_t ensemble_intersection(ensemble_t e1, ensemble_t e2) {
    uint16_t mask = 0x1;
    ensemble_t ei = 0x0;


    for (uint8_t i = 0; i < 16; i++, mask*2) {
    	if (BIT(e1, i) & BIT(e2, i))
	    SET_BIT (ei, i);
    }

    return ei;
}

ensemble_t ensemble_complementaire(ensemble_t e) {
    return ((uint16_t)pow(2, 16)) - e;
}

void ensemble_ajouter_elt(ensemble_t *e, uint16_t numero_elt) {
    SET_BIT (*e, numero_elt);
}

void ensemble_retirer_elt(ensemble_t *e, uint16_t numero_elt) {
    CLEAR_BIT (*e, numero_elt);
}

void ensemble_afficher(const char *msg, ensemble_t e) {
    printf (msg);
    for (int8_t i = 15; i >= 0; i--) {
	printf ("%d", BIT(e, i));
    }
    printf ("\n");
}
