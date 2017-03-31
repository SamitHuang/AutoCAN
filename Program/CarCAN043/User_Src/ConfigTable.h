/***************************************************************************
 *
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file ConfigTable.h
 * @author huangyongxiang(huangyongxiang@baidu.com)
 * @date 2016/01/06
 * @brief 用于分配EEPROM存储空间，以读取和存储系统参数
 *
 **/

#ifndef __CONFIG_TABLE_H
#define __CONFIG_TABLE_H
//
#include "stm32f10x.h"

typedef struct config_table_tt
{
float version;
float startstop;

}config_table_t;

extern config_table_t table;	
extern uint8_t gParamsSaveEEPROMRequset;

u8 LoadParamsFromEEPROM(void);
void ParamSetDefault(void) ;
void ParamToTable(void);
void TableToParam(void);
void TableWriteEEPROM(void);
void TableReadEEPROM(void);
void SaveParamsToEEPROM(u8);

#endif
