/*
 * uart.h
 *
 *  Created on: Dec 4, 2025
 *      Author: DELL
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "software_timer.h"
#include "stdio.h"
#include "string.h"

enum CommandType
{
	NONE,
	RST,
	OK
};

enum UartCommunicationState
{
	INIT,
	WAITING,
	SENDING,
	WAIT_ACK
};

enum CommandParserState
{
	CMD_WAIT,
	CMD_GET
};



#define MAX_BUFFER_SIZE 64

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t str[13];

extern uint32_t ADC_value;

extern enum CommandType command_data;
extern uint8_t command_flag;

extern enum UartCommunicationState FSM_UART_STATE;
extern enum CommandParserState FSM_CMD_PARSER_STATE;

void get_uart_message(UART_HandleTypeDef *huart);
void fsm_command_parser();
void fsm_uart_communication();


#endif /* INC_UART_H_ */
