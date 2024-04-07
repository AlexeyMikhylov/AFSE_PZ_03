#include <stdio.h>
#include <stdlib.h>

// Структура для элемента стека
struct Node {
    int data;
    struct Node* next;
};

// Функция для инициализации стека
struct Node* initStack() {
    return NULL;
}

// Функция для добавления элемента в стек
void push(struct Node** top_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*top_ref);
    (*top_ref) = new_node;
}

// Функция для удаления верхнего элемента из стека
int pop(struct Node** top_ref) {
    if (*top_ref == NULL) {
        printf("Stack is empty\n");
        return -1;
    }

    struct Node* temp = *top_ref;
    *top_ref = (*top_ref)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}

// Функция для сортировки чисел методом подсчета
void countingSortUsingStack(const char* filename) {
    struct Node* stack = initStack();
    int min = 0, max = 0;

    // Открываем файл
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        return;
    }

    // Находим минимальное и максимальное числа
    while (!feof(file)) {
        int num;
        fscanf(file, "%d", &num);
        if (num < min) min = num;
        if (num > max) max = num;
        push(&stack, num);
    }
    fclose(file);

    // Используем массив для подсчёта
    int range = max - min + 1;
    //int count[range];

    // Динамическое выделение памяти для массива count
    int* count = (int*)malloc(range * sizeof(int));
    if (count == NULL) {
        printf("Error while memory allocation\n");
        return;
    }

    // Инициализация count
    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }

    // Подсчитываем числа
    while (stack != NULL) {
        count[stack->data - min]++;
        pop(&stack);
    }

    // Выводим отсортированные числа
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        return;
    }

    while (!feof(file)) {
        int num;
        fscanf(file, "%d", &num);
        if (count[num - min] > 0) {
            printf("%d ", num);
            count[num - min]--;
        }
    }
    fclose(file);

    free(count);
}

int main() {
    countingSortUsingStack("input.txt");

    return 0;
}