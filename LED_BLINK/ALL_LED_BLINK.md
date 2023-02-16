# ALL_LED_BLINK

made by kimminse

## 소개

모든 LED를 동시에 BLINK

보드에 내장 되어 있는 LED 점등

## 보드
**회사 자체 설계 보드**


- F_CPU: 2000000UL

**사용 핀**
  - PH7
  - PH6
  - PH5
  - PH4

**사용 레지스터**
- 데이터 출력값 레지스터 OUT
- 데이터 출력값 레지스터 DIR

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
## 결과
https://user-images.githubusercontent.com/85288381/216195442-5a35bffb-d909-456b-b1d5-6baa9ce89848.mp4