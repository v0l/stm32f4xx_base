#include <CMSIS/device/ST/stm32f4xx.h>

#define LED_BANK        GPIOD
#define LED_ORANGE      13
#define LED_GREEN       12
#define LED_RED         14
#define LED_BLUE        15

static void delay(int n)
{
    for(int x = 0; x< n * 1000; x++)
    {
        __NOP();
    }
}

int main(int, char**) 
{
    RCC->AHB1ENR = RCC_AHB1ENR_GPIODEN;
    LED_BANK->MODER = (1 << (2 * LED_ORANGE)) | (1 << (2 * LED_GREEN)) | (1 << (2 * LED_RED)) | (1 << (2 * LED_BLUE));
    
    
    while(1)
    {
        LED_BANK->ODR ^= (1 << LED_GREEN);
        delay(100);
        LED_BANK->ODR ^= (1 << LED_ORANGE);
        delay(100);
        LED_BANK->ODR ^= (1 << LED_RED);
        delay(100);
        LED_BANK->ODR ^= (1 << LED_BLUE);
        delay(100);
    }
}