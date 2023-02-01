# BinaryPrinter

made by Wooseok Diaa Hwang

## 소개

모든 LED를 동시에 BLINK

보드에 내장 되어 있는 LED 점등

## 보드
**회사 자체 설계 보드**


- F_CPU: 2000000UL

사용 핀
  - PH7
  - PH6
  - PH5
  - PH4

## 코드

```C
#define F_CPU 2000000UL

#include <avr/io.h>
#include "util/delay.h"

int main(void)
{
    /* Replace with your application code */
    // 핀 설정
	PORTH_DIR = 0xF0;
	PORTH_OUT = 0xF0;
	
    while(1)
    {
        //모든 LED 키기
	    PORTH_OUT = 0x00;
	    _delay_ms(500);
        //모든 LED 끄기
        PORTH_OUT = 0xF0;
        _delay_ms(500);
    }
}
```