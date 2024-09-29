#include "reader.h"

TaskList * readFile(char *filename){
    int nbTask;
    TaskList * tasklist;
    Task *task;
    uint64_t time_to_exec = 0, available = 0, deadline = 0;
    uint16_t priority = 0;
    FILE *file = fopen(filename, "r");
    // Opening of file
    if (file == NULL) {
        printf("Error opening file!\n");
        goto fail_allocation;
    }

    // Creating of tasklist
    tasklist = createTaskList(nbTask);
    if(tasklist == NULL){
        printf("Error creating TaskList!\n");
        goto fail_allocation;
    }

    // Scanning of file
    fscanf(file, "%d", &nbTask);
    // printf("Number of task: %d\n", nbTask);
    for (int i = 0; i < nbTask; i++) {
        fscanf(file, "%lu %hd %lu", &time_to_exec, &priority, &deadline);
        task = createTask(time_to_exec,available, deadline, priority);
        if(task == NULL){
            printf("Error creating Task!\n");
            goto fail_allocation;
        }
        task->available = 0;
        task->overdue = false;
        addTaskToTaskList(tasklist, task);
    }

    // Closing of file
    fclose(file);
    return tasklist;
fail_allocation:
    if(file != NULL){
        fclose(file);
    }
    if(tasklist){
        freeTaskList(tasklist);
    }
    return NULL;
}