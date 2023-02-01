# Sequence_bit_LED

made by kimminse

## 소개

bit 계산을 활용한 순서대로 LED 키기

## 보드
**회사 자체 설계 보드**

- F_CPU: 2000000UL

**사용 핀**
  - PH7
  - PH6
  - PH5
  - PH4

## 코드

```C
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 2000000UL

int main(void)
{
    /* Replace with your application code */
	// 핀 설정
	PORTH_DIR = 0xF0;
	PORTH_OUT = 0xF0;
	// 변수
	unsigned char buff;
	buff = 0x00;
	
    while(1)
    {
	    PORTH_OUT = buff; // 비트의 값을 가지고 있는 buff로 점등
	    _delay_ms(500);
	    
	    if(buff == 0xFF) // 모든 LED가 꺼지면 if를 통과
	    {
		    buff = 0x00; // 모든 LED를 킴
	    }
	    else
	    {
		    buff = (buff << 1) + 1; // 1비트씩 이동하며 값을 1로 바꿈
	    }
    }
}
```