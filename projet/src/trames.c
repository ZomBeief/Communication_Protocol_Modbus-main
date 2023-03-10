// modbusTP.c
//
#include <string.h>

#include "Modbus.h"

#include "trames.h"
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
/**
 * It opens a serial port, sets the parameters, and returns the handle
 * 
 * @return A handle to the serial port.
 */
HANDLE connectionSerialPort()
{
    BOOL connexionOk = FALSE;
    HANDLE handleSerialPort = NULL;

	int com_port;
	scanf("COM : %d\n",&com_port);
	handleSerialPort = createSerialPort(com_port);
if (setParamSerialPort(handleSerialPort, SRL_BAUDRATE, SRL_BYTE_SZ, SRL_PARITY, SRL_STOPBIT) == 0)
		return NULL;

    return handleSerialPort;
	}


/**
 * It creates a trame to send to the regulator
 * 
 * @param i_requestType The type of request to be sent to the PLC.
 * @param i_trameSend The trame to send to the PLC.
 * @param i_typeVal This is a pointer to a variable of type TypeVal.
 * 
 * @return The length of the trame to send to the PLC.
 */
ErrorComm createRequestTrame(TypeRequest i_requestType, TRAMES_HANDLER * trames)
{
	int startAdress, nbParamsToread;

	switch(i_requestType)
	{		
		case REQUEST_READ:{
            scanf("Start address : %d\n", &startAdress);

			int nb_parameters;
            scanf("Count : %d\n", &nb_parameters);

			/* Creating the trames to send to the regulator. */
			for (int channel=0; channel < MODBUSREG_CHANNEL_SZ; channel++)
				trames[channel].lengthTrameToSend = makeTrameLecModBus(MODBUSREG_ADRESS, MODBUS_FUNCTION_READ_NWORDS, startAdress + (MODBUSREG_OFFSET * channel), nb_parameters, trames[channel].trameToSend, INTEL);
			
			break;}

		case REQUEST_WRITE:{
			scanf("Start address : %d\n", &startAdress);

			/* Asking the user to enter the number of values to write. */
			int values_sz;
			do
			{
				scanf("Count : %d\n",&values_sz);
			} while (values_sz > ARRAY_MAX_SIZE); //array size limit
			
			/* Asking the user to enter the values to write. */
			short values_arr[ARRAY_MAX_SIZE];
			for (int val_arr_index = 0; val_arr_index < values_sz; val_arr_index++)
			{
				do
				{
					printf("Enter the value [%d]: \n",val_arr_index);
					scanf("%d\n",&values_arr[val_arr_index]);

				}while (abs(values_arr[val_arr_index]) > 32767); //type limit
			}

			/* Creating the trames to send to the regulator. */
			for (int channel=0; channel < MODBUSREG_CHANNEL_SZ; channel++)
				trames[channel].lengthTrameToSend = makeTrameEcrModBusFromShortTab(MODBUSREG_ADRESS, MODBUS_FUNCTION_WRITE_WORDS, startAdress + (MODBUSREG_OFFSET * channel), values_arr, values_sz, trames[channel].trameToSend, INTEL);
			break;}
		default:
			printf("Error\n");
			return ERRORCOMM_EVENT;
			break;
	}
	return ERRORCOMM_NOERROR;
}

ErrorComm parseModbusResponse(char* i_trameReceive, int i_lengthTrameReceived, TypeRequest i_requestType, TypeVal i_typeVal)
{
	ErrorComm codret = ERRORCOMM_ERROR;

	char value_buffer[ARRAY_MAX_SIZE];
	int  nb_values_buffer, adress_buffer, codeFunction_buffer;

	switch (i_requestType)
	{
	case REQUEST_READ:
		switch (i_typeVal)
		{
		case TYPE_SHORT:
			
			short readen_value= 0;
			/* Parsing the received trame. */
			codret = parseTrameModBus(i_trameReceive, i_lengthTrameReceived, value_buffer, &nb_values_buffer, &adress_buffer, &codeFunction_buffer, INTEL);

			/* Printing the values received from the PLC. */
			for (int nb_param = 0;nb_param<nb_values_buffer;nb_param++)
			{
				/* Converting the received value from the PLC to a short value. */
				readen_value = ModBusShortAsciiToIeee(&value_buffer[nb_param*2], INTEL);

				printf("Received value = %d\n", readen_value);
			}
			break;
		
		default:
			break;
		}
		break;
	
	default:
		break;
	}
	return codret;
}
