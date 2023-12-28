#include "debug.h"

#include "storage.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    Delay_Init();
    USART_Printf_Init(115200);

    printf("SystemClk:%d\r\n", SystemCoreClock);

    storage_init();
    
    while(1) {};
}
