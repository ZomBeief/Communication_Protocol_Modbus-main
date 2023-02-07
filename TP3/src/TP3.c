// modbusTP.c
//
#include <string.h>

#include "Modbus.h"
#include "TP3.h"

int GlobaleAdresseRegulatorModbus = 1;

void printState(ErrorComm codret)
{
	switch(codret)
	{
		case ERRORCOMM_BCC:{
			printf("\nError BCC\n");
		break;}

		case ERRORCOMM_TIMEOUT:{
			printf("\nError Timeout\n");
		break;}

		case ERRORCOMM_NOERROR:{
			printf("\nNo error\n");
		break;}

		case ERRORCOMM_ERROR:{
			printf("\nError\n");
		break;}

		default:{
			printf("\nError\n");
		break;}
	}
	return;
}

SOCKET connectionTCPIpPort()
{
    BOOL connexionOk = FALSE;
    SOCKET idConnexionSocket = INVALID_SOCKET;

    // A COMPLETER

    return idConnexionSocket;
}

HANDLE connectionSerialPort()
{
    BOOL connexionOk = FALSE;
    HANDLE handleSerialPort = NULL;

     // A COMPLETER

    return handleSerialPort;
}

int createRequestTrame(TypeRequest i_requestType, char* i_trameSend, TypeVal* i_typeVal)
{
	int lengthTrameSend = 0;
	int startAdress = 0;
	int nbParamsToread = 0;

	switch(i_requestType)
	{
		// Demande de lecture:
		case REQUEST_READ:{
			printf("\n DEMANDE DE LECTURE\n");

			printf("A partir de quelle adresse souhaitez-vous lire?\n");
            scanf("%d", &startAdress);

			printf("Quel type de parametre voulez-vous lire? 0 (short) / 1 (int) / 2 (float)\n");
            scanf("%d", i_typeVal);

            // A COMPLETER

			break;}

		// Deamnde d'ecriture
		case REQUEST_WRITE:{
			printf("\n DEMANDE D'ECRITURE\n");

			printf("A partir de quelle adresse souhaitez-vous ecrire?\n");
            scanf("%d", &startAdress);
			printf("Quel type de parametre voulez-vous ecrire? 0 (short) / 1 (int) / 2 (float)\n");
            scanf("%d", i_typeVal);
			printf("Entre la valeur a ecrire?\n");

            // A COMPLETER

			break;}
	}

	return lengthTrameSend;
}

ErrorComm parseModbusResponse(char* i_trameReceive, int i_lengthTrameReceived, TypeRequest i_requestType, TypeVal i_typeVal)
{
	ErrorComm codret = ERRORCOMM_ERROR;
	
    // A COMPLETER

	return codret;
}
