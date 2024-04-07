#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

struct Stack {
    int top;
    int capacity;
    int* array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}

void countingSortUsingStack(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    int max = 0;
    int num, i;
    while (fscanf(file, "%d", &num) == 1) {
        if (num > max)
            max = num;
    }
    fclose(file);

    struct Stack* countStack = createStack(max + 1);
    int countArray[max + 1];

    for (i = 0; i < max + 1; i++)
        countArray[i] = 0;

    file = fopen(filename, "r");

    while (fscanf(file, "%d", &num) == 1)
        countArray[num]++;

    fclose(file);

    for (i = max; i >= 0; i--) {
        while (countArray[i] > 0) {
            push(countStack, i);
            countArray[i]--;
        }
    }

    file = fopen(filename, "w");

    while (!isEmpty(countStack))
        fprintf(file, "%d ", pop(countStack));

    fclose(file);

    free(countStack->array);
    free(countStack);
}

int main() {
    char filename[] = "numbers.txt";
    countingSortUsingStack(filename);

    printf("Сортировка подсчётом завершена. Результат записан в файл %s.\n", filename);

    return 0;
}