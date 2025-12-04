/*
 * scheduler.h
 *
 *  Created on: Nov 19, 2025
 *      Author: DELL
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include <stdint.h>

enum ErrorCode
{
    INIT_SCHED,
    ERROR_SCH_TOO_MANY_TASKS,
    ERROR_SCH_CANNOT_DELETE_TASK,
    ERROR_SCH_EMPTY
};
enum ReturnCode
{
    RETURN_ERROR,
    RETURN_NORMAL,
    RETURN_ADD_ERROR,
    RETURN_DELETE_ERROR
};

void SCH_Init(void);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

uint32_t SCH_Delete_Task(const uint32_t taskID);

void SCH_Report_Status(void);
void SCH_Go_To_Sleep(void);

#endif /* INC_SCHEDULER_H_ */
