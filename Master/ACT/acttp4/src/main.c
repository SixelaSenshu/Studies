#include <stdio.h>
#include <stdlib.h>
#include "scheduling.h"
#include "task.h"
#include "reader.h"
#include "macro.h"
#include "heuristic.h"
#include "neighborhood.h"

static void printfmenu();

int main(int argc, char *argv[]){

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    char fdir [20] = "./data/";
    char fname [40];
    char fname2 [40];
    char fname3 [40];
    char fname4 [40];
    char fname5 [40];
    TaskList * tasklist;
    Scheduling * sheduling;
    uint64_t solution;
    char choice = '\0';
    printf("File used for tests :\n");
    //1
    sprintf(fname, "%s%s", fdir, "n100_85_b.txt");
    printf("%s\n", fname);
    tasklist = readFile(fname);
    sheduling = addTaskListToScheduling(tasklist);  
    solution = getDelay(sheduling);
    printf("Delay of %s is %ld\n", fname, solution);
    freeTaskList(tasklist);
    // 2
    sprintf(fname2, "%s%s", fdir, "n100_86_b.txt");
    printf("%s\n", fname2);
    tasklist = readFile(fname2);
    sheduling = addTaskListToScheduling(tasklist);  
    solution = getDelay(sheduling);
    printf("Delay of %s is %ld\n", fname2, solution);
    freeTaskList(tasklist);
    //3
    sprintf(fname3, "%s%s", fdir, "n100_35_b.txt");
    printf("%s\n", fname3);
    tasklist = readFile(fname3);
    sheduling = addTaskListToScheduling(tasklist);  
    solution = getDelay(sheduling);
    printf("Delay of %s is %ld\n", fname3, solution);
    freeTaskList(tasklist);
    //4
    snprintf(fname4, sizeof(fname4), "%s%s", fdir, "n100_36_b.txt");
    printf("%s\n", fname4);
    tasklist = readFile(fname4);
    sheduling = addTaskListToScheduling(tasklist);  
    solution = getDelay(sheduling);
    printf("Delay of %s is %ld\n", fname4, solution);
    freeTaskList(tasklist);
    //5
    snprintf(fname5, sizeof(fname5), "%s%s", fdir, "n100_39_b.txt");
    printf("%s\n", fname5);
    tasklist = readFile(fname5);
    sheduling = addTaskListToScheduling(tasklist);  
    solution = getDelay(sheduling);
    printf("Delay of %s is %ld\n", fname5, solution);
    freeTaskList(tasklist);
    printfmenu();
    printf("Choice : ");
    scanf("%c",&choice);
    int i = 0;
    int value = 10;
    switch (choice){
    case '-':
        tasklist = readFile(fname);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname, solution);
        freeTaskList(tasklist);
        value = 20;
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname)){
                i++;
                printf("Better solution found for %s\n",fname);
            }
        }
        printf("Better solution found %d times on %d\n",i,value);
        tasklist = readFile(fname);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        tasklist = readFile(fname);
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        freeTaskList(tasklist);
        tasklist = readFile(fname);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        freeTaskList(tasklist);
        tasklist = readFile(fname);
        if(VND(tasklist, fname)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        // freeTaskList(tasklist);
        break;
    case '0': // GetValues of files
        tasklist = readFile(fname);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname, solution);
        freeTaskList(tasklist);
        tasklist = readFile(fname2);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname2, solution);
        freeTaskList(tasklist);
        tasklist = readFile(fname3);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname3, solution);
        freeTaskList(tasklist);
        tasklist = readFile(fname4);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname4, solution);
        freeTaskList(tasklist);
        tasklist = readFile(fname5);
        sheduling = addTaskListToScheduling(tasklist);
        solution = getDelay(sheduling);
        printf("Delay of %s is %ld\n", fname5, solution);
        freeTaskList(tasklist);
        freeScheduling(sheduling);
        break;
    case '1': // Shuffle
        /**printf("-----------------------------------------\n");
        printf("-------------  Shuffle ------------------\n");
        printf("-----------------------------------------\n");*/
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname)){
                i++;
                printf("Better solution found for %s\n",fname);
            }
        }
        printf("Better solution found %d times on %d\n",i,value);
        i = 0;
        printf("------------------------------------------------------\n");
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname2)){
                i++;
                printf("Better solution found for %s\n",fname2);
            }
        }
        printf("Better solution found %d times on %d\n",i,value);
        i = 0;
        printf("------------------------------------------------------\n");
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname3)){
                i++;
                printf("Better solution found for %s\n",fname3);
            }
        }
        printf("Better solution found %d times on %d\n",i,value);
        i = 0;
        printf("------------------------------------------------------\n");
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname4)){
                i++;
                printf("Better solution found for %s\n",fname4);
            }
        }
        printf("Better solution found %d times on %d\n",i,value);
        i = 0;
        printf("------------------------------------------------------\n");
        for(int ind = 0; ind < value; ind++){
            if(compareRandomShuffle(fname5)){
                i++;
                printf("Better solution found for %s\n",fname5);
            }
        }

        printf("Better solution found %d times on %d\n",i,value);
        break;
    case '2': // Heuristic with deadline
        /**printf("-----------------------------------------\n");
        printf("-------------  Deadline -----------------\n");
        printf("-----------------------------------------\n");*/
        tasklist = readFile(fname);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname2);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname3);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname4);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname5);
        if(heuristic_building_with_deadline(tasklist)){
            printf("Heuristic deadline is better\n");
        }else{
            printf("Heuristic deadline is not better\n");
        }
        freeTaskList(tasklist);
        break;
    case '3': // Heuristic with priority
        /**printf("-----------------------------------------\n");
        printf("-------------  Priority -----------------\n");
        printf("-----------------------------------------\n");*/
        tasklist = readFile(fname);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        sprintf(fname2, "%s%s", fdir, "n100_15_b.txt");
        printf("%s\n", fname2);
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname2);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname3);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname4);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname5);
        if(heuristic_building_with_priority(tasklist)){
            printf("Heuristic priority is better\n");
        }else{
            printf("Heuristic priority is not better\n");
        }
        freeTaskList(tasklist);
        break;
    case '4': // Heuristic with exec
        /**printf("-----------------------------------------\n");
        printf("-------------  Execution ----------------\n");
        printf("-----------------------------------------\n");*/
        tasklist = readFile(fname);
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        printf("%s\n", fname2);
        freeTaskList(tasklist);
        tasklist = readFile(fname2);
        printf("------------------------------------------------------\n");
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        freeTaskList(tasklist);
        tasklist = readFile(fname3);
        printf("------------------------------------------------------\n");
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname4);
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname5);
        if(heuristic_building_with_exec(tasklist)){
            printf("Heuristic exec is better\n");
        }else{
            printf("Heuristic exec is not better\n");
        }
        freeTaskList(tasklist);
        break;
    case '5': // VND
        /*printf("-----------------------------------------\n");
        printf("-------------  VND ----------------------\n");
        printf("-----------------------------------------\n");*/
        tasklist = readFile(fname);
        if(VND(tasklist,fname)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname2);
        if(VND(tasklist,fname2)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");        
        tasklist = readFile(fname3);
        if(VND(tasklist, fname3)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname4);
        if(VND(tasklist,fname4)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        freeTaskList(tasklist);
        printf("------------------------------------------------------\n");
        tasklist = readFile(fname5);
        if(VND(tasklist, fname5)){
            printf("VND is better\n");
        }else{
            printf("VND is not better\n");
        }
        freeTaskList(tasklist);
        break;
    default: // Error choice
        break;
        }

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return EXIT_SUCCESS;
}

static void printfmenu(){
    printf("------------------------------------------------------\n");
    printf("Choice :\n");
    printf("- All test with a file\n");
    printf("0 - Get values of files\n");
    printf("1 - Shuffle\n");
    printf("2 - Heuristic with deadline\n");
    printf("3 - Heuristic with priority\n");
    printf("4 - Heuristic with execution\n");
    printf("5 - VND\n");
    printf("6 - ILS\n"); // To do
    printf("------------------------------------------------------\n");
}
