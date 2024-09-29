#include "heuristic.h"

static bool merge_partition_sort_by_dealine(Task ** listElt, int start, int middle,int end);
static bool merge_partition_sort_by_priority(Task ** listElt, int start, int middle, int end);

bool heuristic_building_with_deadline(TaskList * tasklist){
    uint64_t late_basic, late_heuristic;
    bool result = false;
    Scheduling * scheduler = NULL; 
    Scheduling * scheduler_heuristic = NULL;
    scheduler = addTaskListToScheduling(tasklist);
    // merge_separate_sort_by_deadline(tasklist->tasks,0,tasklist->size);
    bubble_sort_by_deadline(tasklist,tasklist->size);
    scheduler_heuristic = addTaskListToScheduling(tasklist);
    late_basic = getDelay(scheduler);
    late_heuristic = getDelay(scheduler_heuristic);
    printf("Late basic: %lu\n",late_basic);
    printf("Late heuristic: %lu\n",late_heuristic);
    if(late_basic > late_heuristic){
        result = true;
    }
    freeScheduling(scheduler);
    freeScheduling(scheduler_heuristic);
    return result;
}

bool heuristic_building_with_priority(TaskList * tasklist){
    uint64_t late_basic, late_heuristic;
    bool result = false;
    Scheduling * scheduler = NULL; 
    Scheduling * scheduler_heuristic = NULL;
    scheduler = addTaskListToScheduling(tasklist);
    // merge_separate_sort_by_priority(tasklist->tasks,0,tasklist->size);
    bubble_sort_by_priority(tasklist,tasklist->size);
    scheduler_heuristic = addTaskListToScheduling(tasklist);
    late_basic = getDelay(scheduler);
    late_heuristic = getDelay(scheduler_heuristic);
    printf("Late basic: %lu\n",late_basic);
    printf("Late heuristic: %lu\n",late_heuristic);
    if(late_basic > late_heuristic){
        result = true;
    }
    freeScheduling(scheduler);
    freeScheduling(scheduler_heuristic);
    return result;
}

bool heuristic_building_with_exec(TaskList * tasklist){
    uint64_t late_basic, late_heuristic;
    bool result = false;
    Scheduling * scheduler = NULL; 
    Scheduling * scheduler_heuristic = NULL;
    scheduler = addTaskListToScheduling(tasklist);
    // merge_separate_sort_by_priority(tasklist->tasks,0,tasklist->size);
    bubble_sort_by_exec(tasklist,tasklist->size);
    scheduler_heuristic = addTaskListToScheduling(tasklist);
    late_basic = getDelay(scheduler);
    late_heuristic = getDelay(scheduler_heuristic);
    printf("Late basic: %lu\n",late_basic);
    printf("Late heuristic: %lu\n",late_heuristic);
    if(late_basic > late_heuristic){
        result = true;
    }
    freeScheduling(scheduler);
    freeScheduling(scheduler_heuristic);
    return result;
}

bool bubble_sort_by_deadline(TaskList * listTask, int size){
    bool result = false;
    if(listTask == NULL){
        return result;
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(listTask->tasks[j]->deadline > listTask->tasks[j+1]->deadline){
                reverse_task(listTask->tasks[j],listTask->tasks[j+1]);
            }
        }
    }
    result = true;
    return result;
}

bool bubble_sort_by_priority(TaskList *listTask, int size){
    bool result = false;
    if(listTask == NULL){
        return result;
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(listTask->tasks[j]->priority > listTask->tasks[j+1]->priority){
            }
            if(listTask->tasks[j]->priority > listTask->tasks[j+1]->priority){
                reverse_task(listTask->tasks[j],listTask->tasks[j+1]);
            }
        }
    }
    result = true;
    return result;
}

bool bubble_sort_by_exec(TaskList *listTask, int size){
    bool result = false;
    if(listTask == NULL){
        return result;
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(listTask->tasks[j]->time_to_exec > listTask->tasks[j+1]->time_to_exec){
            }
            if(listTask->tasks[j]->time_to_exec > listTask->tasks[j+1]->time_to_exec){
                reverse_task(listTask->tasks[j],listTask->tasks[j+1]);
            }
        }
    }
    result = true;
    return result;
}

bool swap_task(Task * task_1,Task * task_2){
    Task * tmp = NULL;
    if(task_1 == NULL || task_2 == NULL){
        return false;
    }
    tmp = task_1;
    task_1 = task_2;
    task_2 = tmp;
    return true;
}

bool reverse_task(Task * task_1,Task * task_2){
    bool tmp_overdue;
    uint64_t tmp_deadline;
    uint64_t tmp_time_to_start;
    uint16_t tmp_priority;
    uint64_t tmp_available_time;
    if(task_1 == NULL || task_2 == NULL){
        return false;
    }
    // overdue
    tmp_overdue = task_1->overdue;
    task_1->overdue = task_2->overdue;
    task_2->overdue = tmp_overdue;
    // available
    tmp_available_time = task_1->available;
    task_1->available = task_2->available;
    task_2->available = tmp_available_time;
    // deadline
    tmp_deadline = task_1->deadline;
    task_1->deadline = task_2->deadline;
    task_2->deadline = tmp_deadline;
    // time_to_exec 
    tmp_time_to_start = task_1->time_to_exec;
    task_1->time_to_exec = task_2->time_to_exec;
    task_2->time_to_exec = tmp_time_to_start;
    // priority
    tmp_priority = task_1->priority;
    task_1->priority = task_2->priority;
    task_2->priority = tmp_priority;
    return true;
}

bool merge_separate_sort_by_deadline(Task ** listTask, int start,int end){
    int middle = 0;
    if(listTask == NULL){
        return false;
    }
    if(start < end){
        middle = (start + end)/2;
        merge_separate_sort_by_deadline(listTask,start,middle);
        merge_separate_sort_by_deadline(listTask,middle+1,end);
        merge_partition_sort_by_dealine(listTask,start,middle,end);
    }
    return true;
}

static bool merge_partition_sort_by_dealine(Task ** listElt, int start, int middle, int end){
    int i = start, j = end, k;
    Task ** t_tasklist= (Task **) malloc(sizeof(Task *) * (end - start));
    if(t_tasklist == NULL){
        return false;
    }

    for (k = start; k < end; k++) {
        if (i < middle && (j >= end || listElt[i]->deadline <=  listElt[j]->deadline)) {
            t_tasklist[i] = listElt[i];
            i = i + 1;
        } else {
            t_tasklist[j] = listElt[j];
            j = j + 1;
        }
    }
    for(int i = start; i < end; i++){
        listElt[i] = t_tasklist[i];
    }
    // freeTaskList(t_tasklist);
    return true;
}

bool merge_separate_sort_by_priority(Task ** listTask, int start,int end){
    int middle = 0;
    if(listTask == NULL){
        return false;
    }
    if(start < end){
        middle = (start + end)/2;
        merge_separate_sort_by_priority(listTask,start,middle);
        merge_separate_sort_by_priority(listTask,middle+1,end);
        merge_partition_sort_by_priority(listTask,start,middle,end);
    }
    return true;
}

static bool merge_partition_sort_by_priority(Task ** listElt, int start, int middle, int end){
   int i = start, j = end, k;
    Task ** t_tasklist= (Task **) malloc(sizeof(Task *) * (end - start));
    if(t_tasklist == NULL){
        return false;
    }

    for (k = start; k < end; k++) {
        if (i < middle && (j >= end || listElt[i]->priority <=  listElt[j]->priority)) {
            t_tasklist[i] = listElt[i];
            i = i + 1;
        } else {
            t_tasklist[j] = listElt[j];
            j = j + 1;
        }
    }
    for(int i = start; i < end; i++){
        listElt[i] = t_tasklist[i];
    }
    // freeTaskList(t_tasklist);
    return true;
}