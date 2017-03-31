/***************************************************************************
 *
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file ConfigTable.c
 * @author huangyongxiang(huangyongxiang@baidu.com)
 * @date 2016/01/06
 * @brief 用于分配EEPROM存储空间，以读取和存储系统参数
 *
 **/

#include "ConfigTable.h"
#include "stmflash.h"
//#include "Control.h"
//#include "imu.h"
#include "SysConfig.h"
//#include "BT.h"
//#include "NRF24L01.h"
//
#define TABLE_ADDRESS (STM32_FLASH_BASE+STM32_FLASH_OFFEST+0)
//用来存放EEPROM列表上的存放的参数变量的信息
config_table_t table;				//tobe improved: config mean in const / eeprom.
//请求保存参数到EEPROM的信号量
uint8_t gParamsSaveEEPROMRequset=0;

#define EEPROM_DEFAULT_VERSION 1

static uint8_t  isEEPROMValid(void)
{
	STMFLASH_Read(TABLE_ADDRESS,(uint16_t *)(&table),2);
	if((int16_t)table.version==EEPROM_DEFAULT_VERSION)
			return 1;
	else
			return 0;
}

//table defalat . if 
void TableResetDefault(void)
{		
		STMFLASH_Write(TABLE_ADDRESS,(uint16_t *)(&(table.version)),2);
}

//load params for EEPROM
void TableReadEEPROM(void)
{
		uint8_t paramNums=sizeof(table)/sizeof(float);

		STMFLASH_Read(TABLE_ADDRESS,(uint16_t *)(&table),paramNums * 2);
}

void TableWriteEEPROM(void)
{
		uint8_t paramNums=sizeof(table)/sizeof(float);

		STMFLASH_Write(TABLE_ADDRESS,(uint16_t *)(&table),paramNums * 2);
}




extern u8 NRFMatched;


void TableToParam(void)
{
		
}


void ParamToTable(void)
{
}

u8 LoadParamsFromEEPROM(void)
{
	u8 startstop=0;
	if(isEEPROMValid())
	{
		u16 temp=0;
			//TableReadEEPROM();
			//TableToParam();
		STMFLASH_Read(TABLE_ADDRESS,(uint16_t *)(&table),4);
		
		
		if((u16)table.startstop==1)
			startstop=1;			
	}
	else
		startstop = 0;
	
	return startstop;
	/*
	else
	{
			//printf("load params from eeprom failed,set default value\r\n");
		
			//ParamSetDefault();//版本检测不对，各项参数设为默认值
			//ParamToTable();
			table.version=EEPROM_DEFAULT_VERSION;
			TableWriteEEPROM();
	}
	*/
}

void SaveParamsToEEPROM(u8 startstop)
{
		//ParamToTable();
	table.version=EEPROM_DEFAULT_VERSION;
	table.startstop=startstop;
	STMFLASH_Write(TABLE_ADDRESS,(uint16_t *)(&table),4);
	//	TableWriteEEPROM();
}

//all default value 
void ParamSetDefault(void) 
{
	 

}
