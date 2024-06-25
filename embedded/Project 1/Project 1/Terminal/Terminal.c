#include"Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("---------------please enter trancation date-------------------\n");
	gets(termData->transactionDate,10);
	EN_terminalError_t state=TERMINAL_OK;
	if (strlen(termData->transactionDate) < 10 || termData->transactionDate == NULL)
		state = WRONG_DATE;
	else
		if (checkFormat(termData) == TERMINAL_OK)
			state = TERMINAL_OK;
		else
			state = WRONG_DATE;
	return state;
}
EN_terminalError_t checkFormat(ST_terminalData_t* termData) {
	EN_cardError_t state = WRONG_DATE;
	if (termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/') {
		if (termData->transactionDate[0] >= '0' && termData->transactionDate[0] <= '3') 
			if (termData->transactionDate[1] >= '0' && termData->transactionDate[1] <= '9')
				if (termData->transactionDate[3] >= '0' && termData->transactionDate[3] <= '1')
					if (termData->transactionDate[4] >= '0' && termData->transactionDate[4] <= '9')
						if (termData->transactionDate[6] == '2')
							if (termData->transactionDate[7] == '0')
								if (termData->transactionDate[8] == '2')
									if (termData->transactionDate[9] == '2')
						state = TERMINAL_OK;
	}
		else
			state = WRONG_DATE;
		return state;
}
EN_terminalError_t isCardExpired(ST_CardData_t* cardData, ST_terminalData_t* termData) {
	EN_terminalError_t state = EXPIRED_CARD;
	if (cardData->CardExpirationDate[3] > termData->transactionDate[3]) //comparing month
	{
		return state = TERMINAL_OK;
	}
	else if (cardData->CardExpirationDate[3] == termData->transactionDate[3]) {//same month
		if (cardData->CardExpirationDate[4] > termData->transactionDate[4])
			return state = TERMINAL_OK;
		else if (cardData->CardExpirationDate[4] == termData->transactionDate[4])
		{
			if (cardData->CardExpirationDate[0] > termData->transactionDate[0])//compare days
				return state = TERMINAL_OK;
			if (cardData->CardExpirationDate[0] == termData->transactionDate[0])
			{
				if (cardData->CardExpirationDate[1] > termData->transactionDate[1])
					return state = TERMINAL_OK;
				else
					return state = EXPIRED_CARD;
			}
		}
		else
			return state = EXPIRED_CARD;
	}
	else if (cardData->CardExpirationDate[3] == 0 && termData->transactionDate[3] == 0) {
		if (termData->transactionDate[4] < cardData->CardExpirationDate[4])
		{
			
			return state = TERMINAL_OK;
		}
		else
			return state = EXPIRED_CARD;

	}
	else
		return state = EXPIRED_CARD;
	
}	
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("-------------------please enter transction amount-------------------\n");
	scanf("%f",& termData->transAmount);
	EN_terminalError_t state = TERMINAL_OK;
	if ( termData->transAmount<=0.0)
		state= INVALID_AMOUNT;
	else
		state= TERMINAL_OK;
	return state;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	float32_t MaxAmount = termData->maxTransAmount;
	float32_t TransferAmount = termData->transAmount;
	if (termData != NULL) {
		if (TransferAmount < MaxAmount)
			return TERMINAL_OK;
		else
			return EXCEED_MAX_AMOUNT;
	}
	else
		return EXCEED_MAX_AMOUNT;

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	termData->maxTransAmount = maxAmount;
	if (termData != NULL) {
		if ( termData->maxTransAmount <= 0)
			return INVALID_MAX_AMOUNT;
		else
			return TERMINAL_OK;
	}
	else
		return INVALID_MAX_AMOUNT;
}
void isCardExpiredtest(ST_CardData_t* cardData, ST_terminalData_t* termData)
{
	printf("Tester name:-   card-22/06  terminal-10/06 \n");
	printf("Function name:-  isCardExpiredtest\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_cardError_t test = isCardExpired(cardData,termData);
	if (test == TERMINAL_OK || test == EXPIRED_CARD) {
		printf("%d\n", test);
		printf("expected:  TERMINAL_OK or EXPIRED_CARD");
		printf("if result is 0 mean TERMINAL_OK ,if 2 means EXPIRED_CARD\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  TERMINAL_OK or   EXPIRED_CARD ");
	}
}
void isBelowMaxAmounttest(ST_terminalData_t* termData) {
	printf("Tester name:-  max=20000 Transfer=25000\n");
	printf("Function name:-  isBelowMaxAmount\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_cardError_t test = isBelowMaxAmount(termData);
	if (test == TERMINAL_OK || test == EXCEED_MAX_AMOUNT) {
		printf("%d\n", test);
		printf("expected:  TERMINAL_OK or EXCEED_MAX_AMOUNT");
		printf("if result is 0 mean TERMINAL_OK ,if 5 means EXCEED_MAX_AMOUNT\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  TERMINAL_OK or   INVALID_AMOUNT ");
	}
}
void  getTransactionDatetest(ST_terminalData_t* termData) {
printf("Tester name:-   22/02/2022 \n");
printf("Function name:-  getTransactionDate\n");
printf("test case 1\n");
printf("Input data:-    ");
EN_cardError_t test = getTransactionDate(termData);
if (test == TERMINAL_OK || test == WRONG_DATE) {
	printf("%d\n", test);
	printf("expected:  TERMINAL_OK or WRONG_DATE");
	printf("if result is 0 mean TERMINAL_OK ,if 1 means WRONG_DATE\n");
	printf("Test pass \n");
}
else {
	printf("Test fails \n");
	printf("Expected result:-  TERMINAL_OK or   WRONG_DATE ");
}

}
void getTransactionAmounttest(ST_terminalData_t* termData) {
	printf("Tester name:-  0 \n");
	printf("Function name:-  getTransactionAmount\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_cardError_t test = getTransactionAmount( termData);
	if (test == TERMINAL_OK || test == INVALID_AMOUNT) {
		printf("%d\n", test);
		printf("expected:  TERMINAL_OK or INVALID_AMOUNT");
		printf("if result is 0 mean TERMINAL_OK ,if 4 means INVALID_AMOUNT\n");
		printf("Test pass \n");
	}
	else {
		printf("Test fails \n");
		printf("Expected result:-  TERMINAL_OK or   INVALID_AMOUNT ");
	}
}
