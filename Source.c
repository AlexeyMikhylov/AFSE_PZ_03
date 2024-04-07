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
    if (new_node == NULL) {
        printf("memory allocation error\n");
        return;
    }
    new_node->data = new_data;
    new_node->next = *top_ref;
    *top_ref = new_node;
}

// Функция для удаления элемента из стека
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

// Функция для сортировки методом подсчета
void countingSort(FILE* file) {
    int num;
    int max = 0;
    int range = 0;
    struct Node* stack = initStack();

    // Чтение чисел из файла и определение максимального числа
    while (fscanf(file, "%d", &num) != EOF) {
        if (num > max) {
            max = num;
        }
        push(&stack, num);
        range++;
    }

    // Выделение памяти и инициализация массива count
    int* count = (int*)malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        printf("memory allocation error\n");
        return;
    }
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Подсчет встречающихся элементов
    while (stack != NULL) {
        int data = pop(&stack);
        count[data]++;
    }

    // Вывод исходного массива
    printf("Original array:\n");
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j < count[i]; j++) {
            printf("%d ", i);
        }
    }

    // Освобождение памяти и завершение программы
    free(count);
}

int main() {
    // Открытие файла для чтения
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error while opening file\n");
        return 1;
    }

    // Сортировка методом подсчета и вывод результатов
    countingSort(file);

    // Закрытие файла
    fclose(file);

    return 0;
}