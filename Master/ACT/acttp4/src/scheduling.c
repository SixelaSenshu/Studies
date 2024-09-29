#include "scheduling.h"

Scheduling * createScheduling(Task *task){
    Scheduling *scheduling = (Scheduling *) malloc(sizeof(Scheduling));
    if(scheduling == NULL){
        return NULL;
    }
    scheduling->task = task;
    scheduling->late = task->time_to_exec;
    scheduling->time_to_start = task->time_to_exec;
    scheduling->next = NULL;
    return scheduling;

}

void freeScheduling(Scheduling *scheduling){
    Scheduling * scheduling_curr;
    Scheduling * scheduling_next;
    scheduling_curr = scheduling;
    scheduling_next = scheduling->next;
    if(scheduling_curr){
        if(scheduling_next != NULL){
            scheduling_next = scheduling->next;
            free(scheduling_curr);
            scheduling_curr = scheduling_next;
        }
        free(scheduling_curr);
    }
}

void displayScheduling(Scheduling *scheduling){
    printf("--------------------\nScheduling: \n");
    Scheduling * scheduling_curr = scheduling;
    int64_t delay = 0;
    while(scheduling_curr->next != NULL){
        delay += scheduling_curr->late;
        scheduling_curr = scheduling_curr->next;
        displayTask(scheduling_curr->task);
    }
    printf("delay %ld\n", delay);
    printf("--------------------\n");
}

uint64_t getDelay(Scheduling *scheduling){
    uint64_t delay = 0;
    Scheduling * scheduling_curr = scheduling;
    while(scheduling_curr->next != NULL){
        delay += scheduling_curr->late;
        scheduling_curr = scheduling_curr->next;
    }
    return scheduling_curr->late;
}

static int64_t min(int64_t a, int64_t b){
    if(a < b){
        return a;
    }
    return b;
}

int addTaskToScheduling(Scheduling *scheduling, Task *task){
    Scheduling *newScheduling = createScheduling(task);
    if(newScheduling == NULL){
        return EXIT_FAILURE;
    }
    scheduling->next = newScheduling;
    newScheduling->late = scheduling->late;
    newScheduling->time_to_start = scheduling->time_to_start + task->time_to_exec;
    int64_t delay = newScheduling->time_to_start - task->deadline;
    if(delay < 0){
        newScheduling->late += -delay;
    }
    return EXIT_SUCCESS;
}

Scheduling * addTaskListToScheduling(TaskList *tasklist){
    if(tasklist == NULL || tasklist->tasks == NULL){
        return NULL;
    }
    int i = 0;
    Task *task = tasklist->tasks[i];
    Scheduling * root_scheduling = createScheduling(task);
    if(root_scheduling == NULL){
        return NULL;
    }
    Scheduling * curr_scheduling = root_scheduling;
    while(i < tasklist->size -1){
        addTaskToScheduling(curr_scheduling, tasklist->tasks[i++]);
        curr_scheduling = curr_scheduling->next;
    }
    return root_scheduling;
}

bool compareRandomShuffle(char * fname){
    TaskList * tasklist = readFile(fname);
    Scheduling * sheduling = addTaskListToScheduling(tasklist);
    freeTaskList(tasklist);
    tasklist = readFile(fname);
    shuffleTaskList(tasklist);
    Scheduling * sheduling_copy = addTaskListToScheduling(tasklist);
    bool result = true;
    uint64_t solution_base = getDelay(sheduling);
    uint64_t solution = getDelay(sheduling_copy);
    if(solution_base<= solution ){
        result = false;
    }else{
        printf("Solution %lu comparing to solution_base: %lu\n", solution,solution_base);
    }
    freeScheduling(sheduling);
    freeScheduling(sheduling_copy);
    // freeTaskList(tasklist);
    return result;
}