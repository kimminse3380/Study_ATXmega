# Sequence_bit_LED

made by kimminse

## 소개

for문을 활용한 순서대로 LED 키기

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
	unsigned char buff[5]={
		0xFF,
		0xE0,
		0xC0,
		0x80,
		0x00,
	};
	
	while(1)
	{
		for (int i=0; i<5; i++)
		{
			PORTH_OUT = buff[i];
			_delay_ms(500);
		}
	}
}
```


## 결과
https://user-images.githubusercontent.com/85288381/217396418-af186873-a03a-4bc7-a66d-305d23b97fd9.mp4