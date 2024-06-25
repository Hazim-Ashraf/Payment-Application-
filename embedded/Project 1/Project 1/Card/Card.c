#include<stdio.h>

#include"Card.h"

EN_cardError_t getCardholderName(ST_CardData_t *carddata) {
	printf("---------------------please enter your Cardname------------------\n");

	gets(carddata->CardHolderName,25);
	if (strlen(carddata->CardHolderName) > 24 || strlen(carddata->CardHolderName) < 20 || carddata->CardHolderName == "NULL") {
		return  1;
		;
	}
	else
		return CARD_OK;

}
EN_cardError_t getCardExpiryDate(ST_CardData_t* carddata) {
	printf("-----------------please enter your Card expiry date------------\n");
	gets(carddata->CardExpirationDate, 5);
	EN_cardError_t state = CARD_OK;

	if (strlen(carddata->CardExpirationDate) > 5 || strlen(carddata->CardExpirationDate) < 5 || carddata->CardExpirationDate == NULL)
		state = WRONG_EXP_DATE;
	else {
		
		if  (  carddata->CardExpirationDate[2] == '/' && CheckFormat(carddata)==CARD_OK) {
			state = CARD_OK;
		}
		else
			state = WRONG_EXP_DATE;
	}		
	return state;
}
EN_cardError_t CheckFormat(ST_CardData_t* carddata) {
	EN_cardError_t state = WRONG_EXP_DATE;
	if (carddata->CardExpirationDate[0] >= '0' && carddata->CardExpirationDate[0] <= '3')
	{
		if (carddata->CardExpirationDate[1] >= '0' && carddata->CardExpirationDate[1] <= '9') 
			if (carddata->CardExpirationDate[3] >= '0' && carddata->CardExpirationDate[3] <= '1')
				if(carddata->CardExpirationDate[3] == '1')
					if (carddata->CardExpirationDate[4] >= '0' && carddata->CardExpirationDate[4] <= '9')
					state = CARD_OK;
			
		
	}
	else
		state=  WRONG_EXP_DATE;
	return state;

}
EN_cardError_t getCardPAN(ST_CardData_t* carddata) {
printf("-----------------please enter you Primamry account number---------------------\n");
	gets( carddata->PrimaryAccountNumber,20);
	if (strlen(carddata->PrimaryAccountNumber) > 19 || strlen(carddata->PrimaryAccountNumber) < 16|| carddata->PrimaryAccountNumber==NULL)
		return 3;
	else
		return 0;
}
void getCardPANtest(ST_CardData_t* carddata) {
	printf("Tester name:-   123456789111111111 \n");
	printf("Function name:-  getCardPAN\n");
	printf("test case 1\n");
	printf("Input data:-    ");
	EN_cardError_t test = getCardPAN(carddata);
	if (test == CARD_OK || test == WRONG_PAN) {
		printf("%d\n", test);
		printf("expected:  CARD_OK or WRONG PAN");
		printf("if result is 0 mean CARD_OK ,if 3 means WRONG_PAN\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  CARD_OK or   WRONG_NAME ");
	}
	
}
void getCardExpiryDatetest(ST_CardData_t* carddata) {
	printf("Tester name:-   22/02 \n");
	printf("Function name:-  getCardExpiryDate\n");
	printf("test case 1\n");
	printf("Input data:-    ");
	EN_cardError_t test = getCardExpiryDate(carddata);
	if (test == CARD_OK || test == WRONG_EXP_DATE) {
		printf("%d\n", test);
		printf("expected:  CARD_OK or WRONG_EXP_DATE");
		printf("if result is 0 mean CARD_OK ,if 2 means WRONG_EXP_DATE\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  CARD_OK or   WRONG_NAME ");
	}

}
void getCardholderNameTest(ST_CardData_t* carddata) {
	printf("Tester name:-   HAzim ashraf shawky mohamed alwakad \n");
	printf("Function name:-  getcardholderName\n");
	printf("test case 1\n");
	printf("Input data:-    ");
	EN_cardError_t test=getCardholderName(carddata);
	if (test == CARD_OK || test == WRONG_NAME) {
		printf("%d\n",test);
		printf("if result is 0 mean CARD_OK ,if 1 means WRONG_NAME\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  CARD_OK or   WRONG_NAME " );
	}

}





