/*
 * scheduler.c
 *
 *  Created on: Nov 19, 2025
 *      Author: DELL
 */

#include "scheduler.h"
#include "traffic_light.h"


typedef struct
{
    // Pointer to the task (must be a ’void (void) ’ function)
    void (*pTask)(void);
    // Delay (ticks) until the function will (next) be run
    uint32_t Delay;
    // Interval (ticks) between subsequent runs. If Preriod == 0 then this is an one-shot task
    uint32_t Period;
    // Incremented (by scheduler) when task is due to execute
    uint8_t RunMe;
    // This is a hint to solve the question below.
    uint32_t TaskID;

} sTask;

typedef struct
{
    sTask data;
    int32_t next;
} Node;

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 50
#define NO_TASK_ID 0

sTask SCH_tasks_G[SCH_MAX_TASKS];
Node arr[SCH_MAX_TASKS];
int32_t head = -1;
int32_t headF = 0; // free head;
enum ErrorCode Error_code_G;

void initArr()
{
    head = -1;
    headF = 0;
    for (int i = 0; i < SCH_MAX_TASKS - 1; ++i)
    {
        arr[i].next = i + 1;
    }
    arr[SCH_MAX_TASKS - 1].next = -1; // set empty flag;
}

void clearData(int32_t idx)
{
    arr[idx].data.pTask = 0;
    arr[idx].data.Delay = 0;
    arr[idx].data.Period = 0;
    arr[idx].data.RunMe = 0;
    arr[idx].data.TaskID = 0;
}

int32_t getFreeIndexArr()
{
    if (headF == -1)
        return -1;

    int32_t idxF = headF;
    headF = arr[headF].next;
    return idxF;
}

void deleteIndex(int32_t idx)
{ // and exchange free slot
    clearData(idx);
    arr[idx].next = headF;
    headF = idx;
}

void addIndex(int32_t idx)
{
    if (head == -1)
    {
        if (arr[idx].data.Delay == 0)
            arr[idx].data.RunMe = 1;
        head = idx;
        arr[head].next = -1;
        return;
    }

    int32_t curr = head;
    int32_t prev = -1;

    while (curr != -1)
    {
        if (arr[curr].data.Delay > arr[idx].data.Delay)
        {
            if (arr[idx].data.Delay == 0)
                arr[idx].data.RunMe = 1;

            arr[idx].next = curr;

            if (prev == -1)
                head = idx;
            else
                arr[prev].next = idx;

            arr[curr].data.Delay -= arr[idx].data.Delay;
            if (arr[curr].data.Delay == 0)
                arr[curr].data.RunMe = 1;
            return;
        }
        arr[idx].data.Delay -= arr[curr].data.Delay;
        prev = curr;
        curr = arr[curr].next;
    }

    if (arr[idx].data.Delay == 0)
        arr[idx].data.RunMe = 1;
    arr[prev].next = idx;
    arr[idx].next = -1;
}
void SCH_Init(void)
{
    initArr();
    Error_code_G = INIT_SCHED;
    // Timer_init();
    // Watchdog_init();
}

void SCH_Update(void)
{
    /* This function will be updated the remaining time of each
 tasks that are added to a queue. It will be called in the interrupt timer, for example
 10 ms.*/
    if (head == -1)
        return;

    if (arr[head].data.Delay > 0)
        --arr[head].data.Delay;

    if (arr[head].data.Delay == 0)
        arr[head].data.RunMe = 1;
}

void SCH_Dispatch_Tasks(void)
{
    while (head != -1 && arr[head].data.RunMe > 0)
    {
        (*arr[head].data.pTask)();
        arr[head].data.RunMe = 0;

        sTask task_backup = arr[head].data;
        int32_t curr_idx = head;

        head = arr[head].next;

        if (head != -1 && arr[head].data.Delay == 0)
        {
            arr[head].data.RunMe = 1;
        }

        arr[curr_idx].next = -1;

        if (task_backup.Period == 0)
        {
            clearData(curr_idx);
            arr[curr_idx].next = headF;
            headF = curr_idx;
        }
        else
        {
            arr[curr_idx].data.Delay = task_backup.Period;
            arr[curr_idx].data.RunMe = 0;
            addIndex(curr_idx);
        }
    }
}
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{ /* This function is used to add a task to the queue.
     It should return an ID that is corresponding with the added task. */
    int32_t idx = getFreeIndexArr();
    if (idx == -1)
    {
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return RETURN_ADD_ERROR;
    }

    arr[idx].data.pTask = pFunction;
    arr[idx].data.Delay = DELAY;
    arr[idx].data.Period = PERIOD;
    arr[idx].data.RunMe = 0;
    arr[idx].data.TaskID = idx;

    addIndex(idx);
    return idx;
}

uint32_t SCH_Delete_Task(const uint32_t idx)
{
    if (head == -1)
    {
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        return RETURN_ERROR;
    }

    int32_t curr = head;
    int32_t prev = -1;

    while (curr != -1)
    {
        if (arr[curr].data.TaskID == idx)
        {
            if (arr[curr].next != -1)
            {
                arr[arr[curr].next].data.Delay += arr[curr].data.Delay;

                if (arr[arr[curr].next].data.Delay == 0)
                {
                    arr[arr[curr].next].data.RunMe = 1;
                }
                else
                {
                    arr[arr[curr].next].data.RunMe = 0;
                }
            }

            if (prev == -1)
            {
                head = arr[curr].next;
            }
            else
            {
                arr[prev].next = arr[curr].next;
            }

            deleteIndex(curr);
            return RETURN_NORMAL;
        }
        prev = curr;
        curr = arr[curr].next;
    }

    return RETURN_ERROR;
}

void SCH_Report_Status() {}
void SCH_Go_To_Sleep() {}
