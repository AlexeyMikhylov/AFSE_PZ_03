#include <stdio.h>
#include <stdlib.h>

// Структура для стека
struct Node {
    int data;
    struct Node* next;
};

// Функция для создания нового узла стека
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Функция для добавления элемента в стек
void push(struct Node** top, int data) {
    struct Node* node = newNode(data);
    node->next = *top;
    *top = node;
}

// Функция для удаления элемента из стека
int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    struct Node* temp = *top;
    *top = (*top)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Функция для сортировки подсчетом
void countingSort(struct Node** stack, int n)
{
    //int output[n + 1];
    /*int* output = (int*)malloc((n + 1) * sizeof(int));
    int count[100001] = { 0 };

    struct Node* current = *stack;

    // Подсчет количества каждого элемента
    while (current != NULL) {
        count[current->data]++;
        current = current->next;
    }

    // Перезапись значений в стек в отсортированном порядке
    for (int i = 0; i <= 10000; i++) {
        while (count[i] >= 1) {
            push(stack, i);
            count[i]--;
        }
    }

    free(output);*/

    int* output = (int*)malloc((n + 1) * sizeof(int));

    // Находим максимальное значение в стеке
    int max_val = INT_MIN;
    struct Node* current = *stack;
    while (current != NULL) {
        if (current->data > max_val)
            max_val = current->data;
        current = current->next;
    }

    int* count = (int*)malloc((max_val + 1) * sizeof(int));
    memset(count, 0, (max_val + 1) * sizeof(int));

    current = *stack;
    while (current != NULL) {
        count[current->data]++;
        current = current->next;
    }

    // Перезаписываем значения в стек в отсортированном порядке
    for (int i = 0; i <= max_val; i++) {
        while (count[i] >= 1) {
            push(stack, i);
            count[i]--;
        }
    }
}

// Функция для вывода стека
void printStack(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* stack = NULL;
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error when opening file");
        return -1;
    }

    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        push(&stack, number);
    }
    fclose(file);

    printf("Original stack:");
    printStack(stack);

    countingSort(&stack, 10000);

    printf("Sorted stack:");
    printStack(stack);

    return 0;
}