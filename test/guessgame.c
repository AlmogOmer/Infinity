#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    time_t t;
    srand((unsigned)time(&t));
    int randomNumber = rand()%21;
    int n;
    printf("This is a guessing game,\nyou have 5 tries to guess my number\n");
    for(int i=1;i<=5;++i){
        printf("This is your %d try\nyou have %d tr%s left\n",i,5-i,(5-i)==1 ? "y" : "ies");
        printf("please enter a number between 0-20:\n");
        scanf("%d",&n);
        if (n == randomNumber){
            printf("Correct number!\n");
            break;
        }
        else if (n<0 || n>20){
            printf("the number is not in the range of 0-20\n");
            continue;
        }
        else {
            if (n>randomNumber)
                printf("the number is smaller then yours\n");
            else {
                printf("the number is larger then yours\n");
            }

        }

    }
    printf("thanks for playing");
    return 0;
}




