#include <stdio.h>
#include <stdlib.h>

// Структура для элемента стека
struct Node
{
    int data;
    struct Node* next;
};

// Функция для инициализации стека
struct Node* initStack() {
    return NULL;
}

// Функция для добавления элемента в стек
void push(struct Node** top_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("memory allocation error\n");
        return;
    }
    new_node->data = new_data;
    new_node->next = *top_ref;
    *top_ref = new_node;
}

void countingSort(FILE* file)
{
    int num;
    int max = INT_MIN;
    int min = INT_MAX;
    int size = 0;

    // Определение максимального и минимального чисел в файле
    while (fscanf(file, "%d", &num) != EOF)
    {
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
        size++;
    }

    // Выделение памяти и инициализация массива count
    int range = max - min + 1;
    int* count = (int*)malloc(range * sizeof(int));
    if (count == NULL)
    {
        printf("memory allocation error\n");
        return;
    }
    for (int i = 0; i < range; i++)
    {
        count[i] = 0;
    }

    // Перевод отрицательных чисел в неотрицательное представление
    fseek(file, 0, SEEK_SET);
    while (fscanf(file, "%d", &num) != EOF) 
    {
        count[num - min]++;
    }

    // Вывод отсортированного массива
    printf("Sorted array:\n");
    for (int i = 0; i < range; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            printf("%d ", i + min);
        }
    }
    printf("\n");

    free(count);
}

int main()
{
    // Открытие файла для чтения
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error while opening file\n");
        return 1;
    }

    // Сортировка методом подсчета и вывод результатов
    countingSort(file);

    // Закрытие файла
    fclose(file);

    return 0;
}