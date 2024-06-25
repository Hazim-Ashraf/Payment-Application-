#include "application.h"

void appStart(void) {
	printf("--------------WELCOME------------\n");
	ST_CardData_t User1;
	EN_cardError_t HolderName = getCardholderName(&User1);
	while (HolderName != CARD_OK)
	{
		printf("---------Wrong name--------Try again\n");
		HolderName = getCardholderName(&User1);
	}
	EN_cardError_t ExpirationDate = getCardExpiryDate(&User1);
	while (ExpirationDate != CARD_OK)
	{
		printf("---------INVALID date--------Try again\n");
		ExpirationDate = getCardExpiryDate(&User1);
	}
	EN_cardError_t PAN = getCardPAN(&User1);
	while (PAN != CARD_OK)
	{
		printf("---------Wrong PAN--------Try again\n");
		PAN = getCardPAN(&User1);
	}


	ST_terminalData_t terminaldata;
	EN_terminalError_t Maxtrans = setMaxAmount(&terminaldata, 50000);

	ST_transaction_t transData = { User1 };
	transData.terminalData.maxTransAmount = terminaldata.maxTransAmount;
	EN_transState_t TransactionData = recieveTransactionData(&transData);
	
	if (TransactionData == DECLINED_INSUFFECIENT_FUND)
		printf("--------INSUFFECIENT FUNDS-------please insert the right amount\n");
	else if (TransactionData == DECLINED_STOLEN_CARD)
		printf("--------Account is blocked------try again another time\n");
	else if (TransactionData == FRAUD_CARD)
		printf("----------PAN not found--------Try again later\n");
	else if (TransactionData == INTERNAL_SERVER_ERROR)
		printf("----------SERVER ERROR--------Try again later\n");
	 if (TransactionData == APPROVED) {
		 EN_terminalError_t Datetrans = getTransactionDate(&terminaldata);
		 strcpy(transData.terminalData.transactionDate,terminaldata.transactionDate);
		 TransactionData = recieveTransactionData(&transData);
		while (Datetrans != TERMINAL_OK)
		{
			printf("----------INVALID DATE--------please insert again\n");
			Datetrans = getTransactionDate(&terminaldata);
			TransactionData = recieveTransactionData(&transData);
		}
		EN_terminalError_t Checkexpire = isCardExpired(&User1, &terminaldata);
		if (Checkexpire == EXPIRED_CARD)
		{
			printf("--------Declined Expired Card------ \n------- end");
		}
		else
		{
			EN_terminalError_t transAmount = getTransactionAmount(&terminaldata);
			EN_terminalError_t ExceedAmount = isBelowMaxAmount(&terminaldata);
			

			while (transAmount != TERMINAL_OK)
			{
				if (transAmount == INVALID_AMOUNT)
				{
					printf("---------INVALID AMOUNT-----please reinsert again\n");
					transAmount = getTransactionAmount(&terminaldata);
				}
			}
			if (ExceedAmount == EXCEED_MAX_AMOUNT)
				printf("-----Limit Exceeded Decline-------END\n");
			else
			{
				transData.terminalData.transAmount = terminaldata.transAmount;
				TransactionData = recieveTransactionData(&transData);
				ST_accountsDB_t accountRefrence;
				EN_serverError_t ValidAccount = isValidAccount(&User1, &accountRefrence);

				if (ValidAccount == ACCOUNT_NOT_FOUND)
				{
					printf("-------invalid account-----END\n");

				}
				else
				{
					EN_serverError_t AmmountAvailable = isAmountAvailable(&terminaldata, &accountRefrence);
					if (AmmountAvailable == LOW_BALANCE)
					{
						printf("----------Declined insufficient Fund---------\n");
					}
					else
					{
						EN_serverError_t Savetrans = saveTransaction(&transData);
						if (Savetrans == SERVER_OK)
						{
							listSavedTransactions();
						}
					}
				}
			}
		}
	}
	printf("-------------THANK YOU FOR USING OUR PAYMENT APPLICATION-------------\n");
	printf("-----------------------BYE----------------------------\n");

}
