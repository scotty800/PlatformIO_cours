#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t uart_mutex;

void task_A(void *pvParameter)
{
    while(1)
    {
        if (xSemaphoreTake(uart_mutex, portMAX_DELAY) == pdTRUE)
        {
            printf("[Task A] Début envoie uart\n");
            vTaskDelay(pdMS_TO_TICKS(200));
            printf("[Task A] Fin envoie uart\n");
            xSemaphoreGive(uart_mutex);
        }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
}

void task_B(void *pvParameter)
{
    while(1)
    {
        if (xSemaphoreTake(uart_mutex, portMAX_DELAY) == pdTRUE)
        {
            printf("[Task B] Début envoie uart\n");
            vTaskDelay(pdMS_TO_TICKS(200));
            printf("[Task B] Fin envoie uart\n");
            xSemaphoreGive(uart_mutex);
        }
    }
    vTaskDelay(pdMS_TO_TICKS(500));
}

void app_main()
{
    printf("\n=== Simulation Mutex UART ===\n");

    uart_mutex = xSemaphoreCreateBinary();
    if (uart_mutex == NULL)
    {
        printf("Erreur création mutex\n");
        while(1);
    }
    else
    {
        printf("Mutex créé avec succès\n");
    }


    xTaskCreate(task_A, "Task A", 2048, NULL, 2, NULL);
    xTaskCreate(task_B, "Task B", 2048, NULL, 2, NULL);
}