#ifndef JEU_H
#define JEU_H

#include <stdbool.h>

#define NOMBRE_QUESTIONS 14
#define NOMBRE_SUSPECTS  24

struct question {
  char * str;
  bool toAsk;
};

/* Attributs des suspects */
#define ANDRE             0b0001001000010001
#define PHILIPPE          0b0001100001000001
#define JEAN_LOUIS        0b0001001001000001
#define FRANCOIS          0b0010001001000001
#define ROBERT            0b0000000011001001
#define CAROLE            0b0011010001000010
#define MELANIE           0b0000100000100010
#define FABIEN            0b0000010000100101
#define PATRICIA          0b0000001000100010
#define BAPTISTE          0b0000000100011101
#define SEBASTIEN         0b0000010001000001
#define OLIVIER           0b0000000101000101
#define NICOLAS           0b0000010000010001
#define LUC               0b0000100001000001
#define SIMON             0b0010000101000001
#define MAXIME            0b0000000011000101
#define CEDRIC            0b0001000010010001
#define PIERRE            0b0000000101000001
#define MARTIN            0b0000001001000001
#define ELODIE            0b0010000100100010
#define VICTOR            0b0000010000011001
#define GEORGES           0b0010100001000001
#define THIERRY           0b0000100001000101
#define CELINE            0b0000000011000010

#endif /* JEU_H */
