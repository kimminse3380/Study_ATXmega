# Timer_Count_LED

made by kimminse

## 소개

Timer를 통한 LED 점등

## 보드
**회사 자체 설계 보드**
- 1000ms
- 2 MHz int. Osc.

**사용 핀**
  - PH7
  - PH6
  - PH5
  - PH4

**사용 레지스터**
- 데이터 출력값 레지스터 OUT
- 데이터 출력값 레지스터 DIR
- 제어 레지스터 CTRLA
- 제어 레지스터 CTRLB
- 인터럽트 제어 레지스터 INTCTRLA

## 코드

```C
#include <avr/io.h>
#include <avr/interrupt.h>



void timer_setup(void)
{
	TCC0.PER = 31250;
	TCC0.CTRLA = ( TCC0.CTRLA & TC0_CLKSEL_gm ) | TC_CLKSEL_DIV64_gc;
	
	//OVERFLWOK  방지 인터럽트
	TCC0.INTCTRLA = ( TCC0.INTCTRLA & ~TC0_OVFINTLVL_gm ) | TC_OVFINTLVL_MED_gc;
}

void port_init(void)
{
	PORTH_DIR = 0xF0;
	PORTH_OUT = 0x00;
	TCC0.CNTL = 0xFF;
}

void timer_LED(){
	if (TCC0.CNT < 15000)
	{
		PORTH_OUT = 0xF0;
	}
	else
	PORTH_OUT = 0x00;
}

int main(void)
{
	/* Replace with your application code */
	
	timer_setup();
	port_init();
	
	while (1)
	{
		timer_LED();
	}
}
```
## 결과
https://user-images.githubusercontent.com/85288381/216552345-28c847dd-4657-44ab-9183-449cece5e1db.mp4
