#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void blink_task(void *pvParameter) 
{
    while (1)
    {
        printf("Led ON\n");
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
        printf("Led OFF\n");
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
    }
}





void app_main()
{
    printf("=== Début du programme ===\n");

    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 1, NULL);
}