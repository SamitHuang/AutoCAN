#include "CommAndroid.h"

char isAndroidCmdUpdated;
uint8_t androidCmd;
extern uint8_t idNew;
extern uint8_t testCode;
uint8_t actionCode;

void CommAndroid(uint8_t c)
{
	static uint8_t state=0;
	static int16_t g_angle[4];
	static uint8_t g_len=0;
	static int16_t sign=1; 
	
//printf("%s",c);
			if(c == '#')									 //接收到查询运动状态命令
      {
				/*
				if(isGimbalRunning == 0)
				  printf( NOT_RUNNING_STRING);//printf("%s",NotRunning);
				else if(isGimbalRunning == 1)
				  printf( RUNNING_STRING);// UART4_printf( UART4,"%s",IsRunning);//printf("%s",IsRunning);
				*/
				//isAndroidCmdUpdated =1;
				//androidCmd = REQ_MOTION_STATUS;
				
		  }
			else if(c == '$')									//反馈位置信息
		  {
				//get_position();
				 isAndroidCmdUpdated =1;
				 androidCmd =REQ_MOTION_POSITION;
		  } 
		  else if(c == 'A')     //????
		  {
				
					isAndroidCmdUpdated =1;
					androidCmd =INTERRUPT;
				
		  }
			else if(c == 'M')
			{
				isAndroidCmdUpdated =1;
				androidCmd =REQ_MOTOR_POSITION ;
			}
			 /*
		   else if(c == '*')                                    //发送*结束当前正在进行的跳舞
		  {
				goon = 0;
		  } */
		  else if(c == 'S'   && state == 0 /* && isGimbalRunning==0*/ ) 
		  {	
		  	  state = 1;
			    g_angle[0] = g_angle[1] = g_angle[2] = g_angle[3] = 0;
		  }
		  else if(c == '-'&& state == 1) 
		  {
				sign = -1;
		  } 
		  else if(c>='0'&&c<='9' && state == 1)
		  {
		  	    g_angle[g_len] = g_angle[g_len] * 10 + c - '0';
		
		  }
		  else if(c == '%'&& state == 1) 
		  {		
			    g_angle[g_len++] *= sign;
			  	sign = 1;
					state = 2;
		  }
		  else if(c == '-'&& state == 2) 
		  {
				sign = -1;
		  } 
		  else if(c>='0'&&c<='9' && state == 2)
		  {
		    
		  	    g_angle[g_len] = g_angle[g_len] * 10 + c - '0';
		
		  }
		  else if(c == '%'&& state == 2) 
		  {	
		        g_angle[g_len++] *= sign;
		  	    sign = 1;
			    state = 3;
		  }
		   else if(c == '-'&& state == 3) 
		  {
				sign = -1;
		  } 
		  else if(c>='0'&&c<='9' && state == 3)
		  {
		    
		  	    g_angle[g_len] = g_angle[g_len] * 10 + c - '0';
		
		  }
		  else if(c == '%'&& state == 3) 
		  {	
		        g_angle[g_len++] *= sign;
		  	    sign = 1;
			    state = 4;
		  }
		   else if(c == '-'&& state == 4) 
		  {
				sign = -1;
		  } 
		  else if(c>='0'&&c<='9' && state == 4)
		  {
		    
		  	    g_angle[g_len] = g_angle[g_len] * 10 + c - '0';
		
		  }
		  else if(c == 'E'&& state == 4) 
		  {	
			  g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				//motion_flag = 1;
				
				
				gimbalAttSet[HEAD_PITCH] = g_angle[0];
				gimbalAttSet[HEAD_YAW] = g_angle[1];
				gimbalAttSet[BODY_YAW] = g_angle[2];
				gimbalVel = g_angle[3];
				
				isAndroidCmdUpdated =1;
				androidCmd = SET_GIMBAL_ATTI;
				
				state =0;
		  }	
			
			else if(c == 'I'&& state == 4) 	//测试用
		  {	
			  g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				//motion_flag = 1;
				
				
				motorPosSet[MOTOR_LEFT_ID] = g_angle[0];
				motorPosSet[MOTOR_RIGHT_ID] = g_angle[1];
				motorPosSet[MOTOR_BOTTOM_ID] = g_angle[2];
				gimbalVel = g_angle[3];
				
				isAndroidCmdUpdated =1;
				androidCmd = SET_MOTOR;
				
				
		  }	
			else if(c == 'W'&& state == 4)	//单独设定各电机转速
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				
				motorSpeed[MOTOR_LEFT_ID] = g_angle[0];
				motorSpeed[MOTOR_RIGHT_ID] = g_angle[1];
				motorSpeed[MOTOR_BOTTOM_ID] = g_angle[2];
				
				isAndroidCmdUpdated=1;
				androidCmd =SET_MOTOR_SPEED;
			}
			else if(c == 'P'&& state == 4) //单独姿态
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				
				gimbalAttSet[HEAD_PITCH] = g_angle[0];
				gimbalAttSet[HEAD_YAW] = g_angle[1];
				gimbalAttSet[BODY_YAW] = g_angle[2];
				isAndroidCmdUpdated=1;
				androidCmd =SET_MOTOR_POS_ONLY;
			}
			else if(c == 'V' && state == 4)
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				isAndroidCmdUpdated=1;
				androidCmd =REQ_VERSION;
			}
			else if(c == 'C' && state == 4)
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				
				idNew = g_angle[3];
				isAndroidCmdUpdated=1;
				androidCmd =CHG_ID;
			}
			else if(c=='T' && state ==4)
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				testCode = g_angle[3];
				isAndroidCmdUpdated=1;
				androidCmd =REQ_MOTOR_TEST;
			}
			else if( c == 'G' && state ==4)
			{
				g_angle[g_len] *= sign;
			  sign = 1;
				g_len = 0;
				state =0;
				
				actionCode = g_angle[3];
				
				isAndroidCmdUpdated=1;
				androidCmd =SET_ACTION;

			}
			

}