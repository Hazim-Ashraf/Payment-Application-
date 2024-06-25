#include "Server.h"


ST_accountsDB_t accountDB[255] = {
	{13000,RUNNING,"0242378365342334134"} ,
	{2300,RUNNING,"9242378365342334100"},
	{200,BLOCKED,"7242378365342334167"},
	{100000,RUNNING,"5242378365342334111"},
	{1000,RUNNING,"4242378365342334188"},
	{1200,BLOCKED,"3342378365342334653"},
	{12000,RUNNING,"2242378365342341368"},
	{15000,BLOCKED,"1242378365342341285"},
	{6700,RUNNING,"3562378365342341918"},
	{5000,BLOCKED,"3972378365343341549"},
};
ST_transaction_t transactionDB[255] = {0};

ST_accountsDB_t accountRefrence;
uint32_t count = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	uint32_t state = 0;
	EN_transState_t res = APPROVED;
	printf("----------------------checking data------------------\n");
	uint32_t found = 0;
	uint32_t amountCheck = 0;
	uint32_t TransctionCount = 0;
	uint32_t flag = 0;
	for (int i = 0; i < 10; i++) {
			if (strcmp(transData->cardHolderData.PrimaryAccountNumber , accountDB[i].primaryAccountNumber)==0 ) {
				found = 1;
				TransctionCount = i;
				break;
			}
	}
		if (transData->terminalData.transAmount < accountDB[TransctionCount].balance)
			amountCheck = 1;
		if (accountDB[TransctionCount].state == transData->transState)
			state = 1;
		if (found == 0 && state == 0 && amountCheck == 0)
			res = INTERNAL_SERVER_ERROR;
		else if (found == 0)
			res = FRAUD_CARD;
		else if (state == 0)
			res = DECLINED_STOLEN_CARD;
		else if (amountCheck == 0)
			res = DECLINED_INSUFFECIENT_FUND;
		else if(found == 1 && state == 1 && amountCheck == 1)
			res = APPROVED;
		else if (res == APPROVED)
			accountDB[TransctionCount].balance -= transData->terminalData.transAmount;

		//printf("%f   new balance:-\n", accountDB[TransctionCount].balance);
		return res;
	}

void recieveTransactionDatatest(void) {
	ST_CardData_t test;
	getCardPAN(&test);
	ST_terminalData_t test1;
	getTransactionAmount(&test1);
	ST_transaction_t test2 = { test,test1,RUNNING,1 };
	//printf("Tester name:-   \n");
	printf("Function name:-  void recieveTransactionData\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_transState_t Test =recieveTransactionData(&test2);
	printf("%d\n", Test);
}
EN_serverError_t isValidAccount(ST_CardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	uint32_t flag = 0;
	uint32_t Accountnum = 0;
	EN_serverError_t found = ACCOUNT_NOT_FOUND;
	for (int i = 0; i < 10; i++) {
		if (strcmp(cardData->PrimaryAccountNumber, accountDB[i].primaryAccountNumber) == 0) {
			found = SERVER_OK;
			Accountnum = i;
			break;
		}
	}

	if (found == ACCOUNT_NOT_FOUND)
	{
		accountRefrence = NULL;
	}
	else {
		accountRefrence->balance = accountDB[Accountnum].balance;
		accountRefrence->state = accountDB[Accountnum].state;
		strcpy(accountRefrence->primaryAccountNumber,accountDB[Accountnum].primaryAccountNumber);
		found = SERVER_OK;
	}
		return found;
}
void isValidAccounttest(void) {
	ST_CardData_t test;
	getCardPAN(&test);
	printf("Function name:-  voidisValidAccount\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_transState_t Test = isValidAccount(&test,& accountRefrence);
	printf("%d\n", Test);
	}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	EN_serverError_t block = SERVER_OK;
	for (int i = 0; i < 10; i++) {
		;
		if (strcmp(accountRefrence->primaryAccountNumber,accountDB[i].primaryAccountNumber) == 0) {
			if(accountDB[i].state==BLOCKED)
			block = BLOCKED_ACCOUNT;
		break;
		}
	}
	return block;
}
void isBlockedAccounttest(void) {
	printf("Function name:-  isBlockedAccount\n");
	printf("test case 1\n");
	printf("Input data:-    \n");

	EN_transState_t Test = isBlockedAccount(&accountRefrence);
	printf("%d\n", Test);
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	EN_serverError_t amount = SERVER_OK;
	for (int i = 0; i < 10; i++) {
		
		if (accountRefrence->balance < termData->transAmount) {
			amount = LOW_BALANCE;
			break;
		}
	}
	return amount;
}
void isAmountAvailabletest(void) {
	ST_terminalData_t test1;
	getTransactionAmount(&test1);
	printf("Function name:-  isAmountAvailable\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_transState_t Test = isAmountAvailable(&test1, &accountRefrence);
	printf("%d\n", Test);
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
		transactionDB[count].cardHolderData = transData->cardHolderData;
		transactionDB[count].terminalData = transData->terminalData;
		transactionDB[count].transState = transData->transState;
		count++;
		transactionDB[count-1].transactionSequenceNumber = count;
	
	return SERVER_OK;
}
void saveTransactiontest(void) {
	ST_CardData_t test;
	getCardPAN(&test);
	ST_terminalData_t test1;
	getTransactionDate(&test1);
	getTransactionAmount(&test1);
	
	ST_transaction_t test2 = { test,test1,RUNNING,count };
	//printf("Tester name:-   \n");
	printf("Function name:-  void saveTransactionData\n");
	printf("test case 1\n");
	printf("Input data:-    \n");
	EN_transState_t Test = saveTransaction(&test2);
	printf("%d\n", Test);
}
void listSavedTransactions(void) {
	
	for (int i = 0; i < count; i++) {
	printf("##########################\n");
	printf("Transaction Sequence Number: %d\n",transactionDB[i].transactionSequenceNumber);
	printf("Transaction Date: %s\n", transactionDB[i].terminalData.transactionDate);
	printf("Transaction Amount: %f\n", transactionDB[i].terminalData.transAmount);
	if(transactionDB[i].transState==0)
		printf("Transaction State: APPROVED\n");
	else if (transactionDB[i].transState == 1)
		printf("Transaction State: DECLINE SUFFICIENT FUNDS\n");
	else if (transactionDB[i].transState == 2)
		printf("Transaction State: DECLINED STOLEN CARD\n");
	else if (transactionDB[i].transState == 3)
		printf("Transaction State: FRAUD CARD\n");
	else if (transactionDB[i].transState == 4)
		printf("Transaction State: INTERNAL SERVER ERROR\n");
	printf("Terminal Max Amount: %f\n",transactionDB[i].terminalData.maxTransAmount);
	printf("Card Holder Name: %s\n", transactionDB[i].cardHolderData.CardHolderName);
	printf("PAN: %s\n", transactionDB[i].cardHolderData.PrimaryAccountNumber);
	printf("Card expiration date: %s\n", transactionDB[i].cardHolderData.CardExpirationDate);
	printf("##########################\n");
	}
}
void listSavedTransactionstest(void) {
	listSavedTransactions();
}

