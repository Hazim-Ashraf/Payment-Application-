#ifndef TERMINAL_H
#define TERMINAL_H

#include  "..\Card\Card.h" 


typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_CardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
void getTransactionAmounttest(ST_terminalData_t* termData);
void isBelowMaxAmounttest(ST_terminalData_t* termData);
void isCardExpiredtest(ST_CardData_t* cardData, ST_terminalData_t* termData);
void  getTransactionDatetest(ST_terminalData_t* termData);

#endif