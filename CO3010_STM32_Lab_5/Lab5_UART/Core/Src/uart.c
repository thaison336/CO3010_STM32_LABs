/*
 * uart.c
 *
 *  Created on: Dec 4, 2025
 *      Author: DELL
 */

#include "uart.h"

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t str[13];

uint32_t ADC_value = 0;

enum CommandType command_data = NONE;
uint8_t command_flag = 0;

enum UartCommunicationState FSM_UART_STATE = INIT;
enum CommandParserState FSM_CMD_PARSER_STATE = CMD_WAIT;

void get_uart_message(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		buffer[index_buffer++] = temp;
		if (index_buffer == MAX_BUFFER_SIZE) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void fsm_command_parser()
{
	switch (FSM_CMD_PARSER_STATE) {
		case CMD_WAIT:

			if (temp == '!') // Change state: CMD_GET
			{
				index_buffer = 0;
				FSM_CMD_PARSER_STATE = CMD_GET;
			}
			break;
		case CMD_GET:

			if (temp == '#') // Change state: CMD_WAIT
			{
				if (buffer[0] == 'R' && buffer[1] == 'S'  && buffer[2] == 'T' && buffer[3] == '#')
				{
					command_data = RST;
					command_flag = 1;
				}
				if (buffer[0] == 'O' && buffer[1] == 'K'  && buffer[2] == '#')
				{
					command_data = OK;
					command_flag = 1;
				}
				FSM_CMD_PARSER_STATE = CMD_WAIT;
			}
			break;
		default:
			break;
	}
}

void fsm_uart_communication()
{
	switch (FSM_UART_STATE) {
		case INIT:

			if (1) // Change state: WAITING
			{
				FSM_UART_STATE = WAITING;
			}
			break;
		case WAITING:

			if (command_flag == 1 && command_data == RST) // Change state: SENDING
			{
				ADC_value = HAL_ADC_GetValue(&hadc1);
				sprintf((char *)str, "\r\n!ADC=%ld#", ADC_value);

				command_flag = 0;
				FSM_UART_STATE = SENDING;
			}
			break;
		case SENDING:
			HAL_UART_Transmit(&huart2, str, sizeof(str) , HAL_MAX_DELAY);

			if (1) // Change state: WAIT_ACK
			{
				setTimer(0, 3000);
				FSM_UART_STATE = WAIT_ACK;
			}
			break;

		case WAIT_ACK:

			if (command_flag == 1 && command_data == OK) // Change state: WAITING
			{
				command_flag = 0;
				FSM_UART_STATE = WAITING;
			}
			if (isFlag(0)) // Change state: SENDING (resend)
			{
				FSM_UART_STATE = SENDING;
			}
			break;
		default:
			break;
	}
}
