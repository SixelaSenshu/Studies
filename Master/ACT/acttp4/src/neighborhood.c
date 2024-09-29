#include "neighborhood.h"

bool VND(TaskList * tasklist, char * filename){
    int nbNeighborhood = 10;
    int step = 0;
    int listnb = 0;
    Neighborhood * neighborhood = createNeighborhood(nbNeighborhood);
    TaskList * newTaskList;
    ListOfTaskList * list;
    TaskList * bestTaskList;
    Scheduling * scheduler = NULL;
    int64_t solution = 0, betterSolution = -1;
    int64_t delay;
    scheduler = addTaskListToScheduling(tasklist);
    delay = getDelay(scheduler);
    betterSolution = delay;
    printf("delay : %ld\n", delay);
    for(int k = 0; k < nbNeighborhood; k++){
        list = createListOfTaskList(nbNeighborhood);
        for(int i = 0; i < nbNeighborhood; i++){
            TaskList * newTaskList = readFile(filename);
            srand((unsigned int)k * i * 5);
            shuffleTaskList(newTaskList);
            addTaskList(list, newTaskList);
        }
        addNeighborhood(neighborhood, list);
    }
    while(listnb < nbNeighborhood){
        newTaskList = list->list[listnb];
        if(scheduler == NULL){
            printf("Error : scheduler is NULL\n");
            solution = 0;
        }else{
            scheduler = addTaskListToScheduling(newTaskList);
            solution = getDelay(scheduler);
        }
        if(solution != 0){
            printf("solution : %ld\n", solution);
            if(solution < betterSolution){
                betterSolution = solution;
                bestTaskList = tasklist;
                step = 0;
                listnb++;
            }else{
                step++;
            }
            if(step == nbNeighborhood){
                listnb++;
                step = 0;
            }
            list = neighborhood->list[step];
        }else{
            step++;
            if(step == nbNeighborhood){
                listnb++;
                step = 0;
            }
            list = neighborhood->list[step];
        }
    }
    printf("Best solution : %ld\n", betterSolution);
    // destroyNeighborhood(neighborhood);
    printf("current delay : %ld\n", delay);
    if(betterSolution < delay){
        return true;
    }
    return false;
}

bool ILS(char * filename){
    //To do
}

ListOfTaskList * createListOfTaskList(int capacity){
    ListOfTaskList * list = malloc(sizeof(ListOfTaskList));
    list->capacity = capacity;
    list->size = 0;
    list->list = malloc(sizeof(TaskList *) * capacity);
    return list;
}

void destroyListOfTaskList(ListOfTaskList * list){
    for(int i = 0; i < list->size; i++){
        freeTaskList(list->list[i]);
    }
    free(list->list);
    free(list);

}

void addTaskList(ListOfTaskList * list, TaskList * tasklist){
    if(list->size < list->capacity){
        list->list[list->size] = tasklist;
        list->size++;
    }

}

void removeTaskList(ListOfTaskList * list, int index){
    if(index < list->size){
        freeTaskList(list->list[index]);
        for(int i = index; i < list->size - 1; i++){
            list->list[i] = list->list[i+1];
        }
        list->size--;
    }
}

void printListOfTaskList(ListOfTaskList * list){
    printf("ListOfTaskList : \n");
    for(int i = 0; i < list->size; i++){
        printf("TaskList %d : \n", i);
        displayTaskList(list->list[i]);
    }
}

Neighborhood * createNeighborhood(int capacity){
    Neighborhood * neighborhood = malloc(sizeof(Neighborhood));
    neighborhood->capacity = capacity;
    neighborhood->size = 0;
    neighborhood->list = malloc(sizeof(ListOfTaskList *) * capacity);
    return neighborhood;
}

void destroyNeighborhood(Neighborhood * neighborhood){
    for(int i = 0; i < neighborhood->size; i++){
        destroyListOfTaskList(neighborhood->list[i]);
    }
    free(neighborhood->list);
    free(neighborhood);
}

void addNeighborhood(Neighborhood * neighborhood, ListOfTaskList * tasklist){
    if(neighborhood->size < neighborhood->capacity){
        neighborhood->list[neighborhood->size] = tasklist;
        neighborhood->size++;
    }
}

void removeNeighborhood(Neighborhood * neighborhood, int index){
    if(index < neighborhood->size){
        removeTaskList(neighborhood->list[index], 0);
        for(int i = index; i < neighborhood->size - 1; i++){
            neighborhood->list[i] = neighborhood->list[i+1];
        }
        neighborhood->size--;
    }
}

void printNeighborhood(Neighborhood * neighborhood){
    printf("Neighborhood : \n");
    for(int i = 0; i < neighborhood->size; i++){
        printf("ListOfTaskList %d : \n", i);
        printListOfTaskList(neighborhood->list[i]);
    }
}