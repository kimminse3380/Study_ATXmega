# Timer_Counter_Interrupt

made by kimminse

## 소개

Timer에서 overflow 인터럽트 발생시 키고 끄기

## 보드
**회사 자체 설계 보드**

**사용 핀**
- PR1/XTAL1
- PR0/XTAL2 
- PH7
- PH6
- PH5
- PH4
- TCC0

**사용 레지스터**
- 데이터 출력값 레지스터 OUT
- 데이터 출력값 레지스터 DIR
- 시스템 클록 제어 레지스터 CTRL
- 시스템 클록 프리스케일러 제어 레지스터 PSCTRL
- 오실레이터 제어 레지스터 CTRL
- 오실레이터 상태 레지스터 STATUS
- 외부 오실레이터 제어 레지스터 XOSCCTRL
- 제어 레지스터 CTRLA
- 제어 레지스터 CTRLB
- 인터럽트 제어 레지스터 INTCTRLA
- PMIC 제어 레지스터 CTRL
- 주기 레지스터 PER

## 코드

```C
#include <avr/io.h>
#include <avr/interrupt.h>

void OSC_Clock_init(void){
	OSC.CTRL &=~OSC_RC2MCREF_bm; //disable RC32M
	// Setting Ext. OSC
	OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_X32KLPM_bm | OSC_XOSCSEL_XTAL_16KCLK_gc;
	OSC.CTRL |= OSC_XOSCSEL_gm;
	do
	{
		// 오실레이터가 안정될 때까지 기다리기
	} while ((OSC.STATUS& OSC_XOSCRDY_bm )==0);
	
	OSC.PLLCTRL = (uint8_t)OSC_PLLSRC_XOSC_gc | 0x2; //32M
	OSC.CTRL |= OSC_PLLEN_bm; // enable PLL
	
	while((OSC.STATUS &  OSC_PLLRDY_bm) == 0); //PLL 준비 기다리기
	CCP = CCP_IOREG_gc;
	CLK.CTRL =  CLK_SCLKSEL_PLL_gc; // PLL을 주 클럭으로 사용
	
}

void timer_setup(void)
{
	TCC0_CTRLA = 0x07; //32000000/1024/(1+31249) = 1Hz
	TCC0_CTRLB = 0x00;
	TCC0_PER = 31249;
	TCC0_CNT = 0x0000;
	
	TCC0_INTCTRLA = 0X03;
	PMIC_CTRL = 0x07;
}

void port_init(void)
{
	PORTH_DIR = 0xF0;
	PORTH_OUT = 0xF0;
	TCC0.CNTL = 0xFF;
}


ISR(TCC0_OVF_vect){
	PORTH_OUTTGL = 0xF0;
}

int main(void)
{
	/* Replace with your application code */
	timer_setup();
	port_init();
	
	sei();
	while(1){
		
	}
}
```
