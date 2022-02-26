#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>

#define SIZE 100

int array[SIZE];
long timearray[SIZE];
int allval;
long timeall;

void setval(int idx, int val){
    if(idx>=SIZE){
        return;
    }
    
    array[idx] = val;
    timearray[idx] = time(NULL);
}

int getval(int idx){
    if(idx>=SIZE){
        return -1;
    }
    
    if(timearray[idx] < timeall){
        return allval;
    }

    else{
        return array[idx];
    }
}

void setall(int val){
    allval = val;
    timeall = time(NULL);
}

static int compare_int(const void *x, const void *y)
{
	return (*(int*)x - *(int*)y);
}

int SumInArray(unsigned int *arr, int size, int sum){
    int start = 0;
    int end = size - 1;

    qsort(arr, size, sizeof(int), compare_int);
    while(end>start){
        if(arr[start] + arr[end] > sum){
            --end;
        }
        else if(arr[start] + arr[end] < sum){
            ++start;
        }
        else{
            return 1;
        }
    }

    return 0;

}

void swap (char *x, char *y)
{
	char temp;
	temp = *y;
	*y = *x; 
	*x = temp; 
}

void reverse(char *arr, int start, int end){
    while(start < end){
        swap (&arr[start], &arr[end]);
        ++start;
        --end;
    }
}


void shiftArray(char *arr, int size, int n){
    /*int i;
    char temp = arr[n];
    for(i = 0; i < n; ++i){
        int idx = ((size -n)*i) % size;
        swap(&arr[idx], &temp);
    }*/

    reverse(arr, 0, size - 1);
    reverse(arr,0,n%size -1);
    reverse(arr,n%size, size - 1);

}









int main(){
    /*setall(5);
    printf("val in idx 4 : %d\n", getval(4));
    setval(3, 1);
    printf("val in idx 4 : %d\n", getval(4));
    printf("val in idx 3 : %d\n", getval(3));
    sleep(1);
    setall(8);
    printf("val in idx 3 : %d\n", getval(3));*/
    
    /*unsigned int arr[] = {2,3,4,9,1,10,6,16,21,5}; /*1,2,3,4,5,6,9,10,16,21*/
    /*printf("%d\n", SumInArray(arr,10,17));*/

    /*char arr[] = {'a', 'b', 'c', 'd'}; 
    shiftArray(arr, 4, 3);
    printf("%s",arr);*/

    
    return 0;
}

