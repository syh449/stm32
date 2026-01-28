#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "key.h"
#include "CountSensor.h"
#include "LED.h"


int yy=0;
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
					yy=0;
			LED1_OFF();//中断使灯灭
		}
		else
		{
			yy=1;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line14);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}




int main(void)
{
	/*模块初始化*/
  Key_Init();
	CountSensor_Init();		//计数传感器初始化
	LED_Init();
	
int keynum=0;
	LED1_OFF();
	yy=0;
	while (1)
	{
			if(yy==0)
		{
			LED1_OFF();
			continue;
		}
		else{
				if(Key_GetNum()==1)
				{
					LED1_ON();
					Delay_s(10);
				}
				LED1_OFF();
      
		}
	
	

		
}
	
}