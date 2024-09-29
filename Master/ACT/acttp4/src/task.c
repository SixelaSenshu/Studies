#include "task.h"

Task * createTask(uint64_t time_to_exec, uint64_t available, uint64_t deadline, uint16_t priority){
    Task *task = (Task *) malloc(sizeof(Task));
    if(task == NULL){
        return NULL;
    }
    task->time_to_exec = time_to_exec;
    task->available = available;
    task->deadline = deadline;
    task->priority = priority;
    task->overdue = false;
    return task;

}

void freeTask(Task *task){
    if(task){
        free(task);
    }
}

void displayTask(Task * task){
    printf("{");
    printf("Time to exec: %lu; ", task->time_to_exec);
    printf("Available: %lu; ", task->available);
    printf("Deadline: %lu; ", task->deadline);
    printf("Priority: %d; ", task->priority);
    printf("Overdue: %d", task->overdue);
    printf("}\n");
}

TaskList * createTaskList(uint16_t size){
    TaskList *taskList = (TaskList *) malloc(sizeof(TaskList));
    if(taskList == NULL){
        return NULL;
    }
    taskList->tasks = (Task **) malloc(sizeof(Task *) * size);
    if(taskList->tasks == NULL){
        free(taskList);
        return NULL;
    }
    taskList->size = 0;
    taskList->capacity = size;
    return taskList;

}

void freeTaskList(TaskList *taskList){
    if(taskList){
        for(int i = 0; i < taskList->size; i++){
            freeTask(taskList->tasks[i]);
        }
        free(taskList->tasks);
        free(taskList);
    }
}

void addTaskToTaskList(TaskList *taskList, Task *task){
    if(taskList->size == taskList->capacity){
        // printf("Overflow of tasks for taskList\n");
    }else{
        taskList->tasks[taskList->size] = task;
        taskList->size++;
    }
}

void displayTaskList(TaskList *taskList){
    printf("--------------------\nTaskList: \n");
    for(int i = 0; i < taskList->size; i++){
        displayTask(taskList->tasks[i]);
    }
    printf("--------------------\n");
}

static void switchTask(Task * task1, Task * task2){
    uint64_t t_avaible = task1->available;
    uint64_t t_deadline = task1->deadline;
    bool toverdue = task1->overdue;
    uint16_t t_priority = task1->priority;  
    uint64_t t_time = task1->time_to_exec;
    task1->available = task2->available;
    task1->deadline = task2->deadline;
    task1->overdue = task2->overdue;
    task1->priority = task2->priority;
    task1->time_to_exec = task2->time_to_exec;
    task2->available = t_avaible;
    task2->deadline = t_deadline;
    task2->overdue = toverdue;
    task2->priority = t_priority;
    task2->time_to_exec = t_time;
}

void shuffleTaskList(TaskList * tasklist){
    int i, j, k;
    // Task * tmp;
    for(k = 0; k < 100; k++){
        for(i = 0; i < tasklist->size; i++){
            j = rand() % tasklist->size;
            j = j * k % tasklist->size;
            switchTask(tasklist->tasks[i], tasklist->tasks[j]);
        }
    }
}

