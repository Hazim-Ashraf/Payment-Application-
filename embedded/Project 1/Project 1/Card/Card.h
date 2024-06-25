#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include  "../Types\Type.h"
typedef struct ST_CardData_t {
	uint8_t CardHolderName[24];
	uint8_t PrimaryAccountNumber[20];
	uint8_t CardExpirationDate[6];
} ST_CardData_t;

typedef enum EN_cardError_t {
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
} EN_cardError_t;

EN_cardError_t getCardholderName(ST_CardData_t* carddata);
EN_cardError_t getCardExpiryDate(ST_CardData_t* carddata);
EN_cardError_t getCardPAN(ST_CardData_t* carddata);
void getCardPANtest(ST_CardData_t* carddata);
void getCardExpiryDatetest(ST_CardData_t* carddata);
void getCardholderNameTest(ST_CardData_t* carddata);




#endif