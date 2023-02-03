# ALL_LED_BLINK

made by kimminse

## 소개

Timer를 통한 LED 점등

## 보드
**회사 자체 설계 보드**

**사용 핀**
  - PH7
  - PH6
  - PH5
  - PH4

## 코드

```C
#include <avr/io.h>
#include <avr/interrupt.h>



void timer_setup(void)
{
    TCC0.PER = 20000;
    TCC0.CTRLA = ( TCC0.CTRLA & TC0_CLKSEL_gm ) | TC_CLKSEL_DIV64_gc;
	
	//OVERFLWOK  방지 인터럽트
    TCC0.INTCTRLA = ( TCC0.INTCTRLA & ~TC0_OVFINTLVL_gm ) | TC_OVFINTLVL_MED_gc;
}
 

int main(void)
{
    /* Replace with your application code */
	PORTH_DIR = 0xF0;
	PORTH_OUT = 0x00;
	TCC0.CNTL = 0xFF;
	
	timer_setup();
	while (1) 
    {
		if (TCC0.CNT < 15000)  
		{
			PORTH_OUT = 0xF0;
		}
		else
			PORTH_OUT = 0x00;
    }
}
```
## 결과