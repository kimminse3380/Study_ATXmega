# Crystal_Timer_Count_LED

made by kimminse

## 소개

XTAL에 연결되어 있는 크리스탈을 클럭으로 설정하고 Timer를 통한 LED 점등

## 보드
**회사 자체 설계 보드**
- 16m
- XTAL

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
- PLL 제어 레지스터 PLLCTRL

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
	
	OSC.PLLCTRL = (uint8_t)OSC_PLLSRC_XOSC_gc | 0x1; //16M
	OSC.CTRL |= OSC_PLLEN_bm; // enable PLL
	CLK.PSCTRL = (uint8_t)CLK_PSADIV_1_gc |  CLK_PSBCDIV_1_1_gc; ////프리스케일러
	
	while((OSC.STATUS &  OSC_PLLRDY_bm) == 0); //PLL 준비 기다리기
	CCP = CCP_IOREG_gc;
	CLK.CTRL =  CLK_SCLKSEL_PLL_gc; // PLL을 주 클럭으로 사용
	
}

void timer_setup(void)
{
	TCC0.PER = 62500;
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
	if (TCC0.CNT < 31250)
	{
		PORTH_OUT = 0xe0;
	}
	else
	PORTH_OUT = 0xF0;
}

int main(void)
{
	/* Replace with your application code */
	OSC_Clock_init();
	timer_setup();
	port_init();
	
	while (1)
	{
		timer_LED();
	}
}
```
## 결과
https://user-images.githubusercontent.com/85288381/217155160-3fd74171-f07c-4bb0-9c4c-f77bf576673f.mp4

확실히 빨라진 것을 볼 수 있다.  