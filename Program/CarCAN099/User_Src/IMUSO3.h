/***************************************************************************
 *
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file IMUSO3.h
 * @author huangyongxiang(huangyongxiang@baidu.com)
 * @date 2016/01/06
 * @brief Inertial Navigation based on nonlinear complementary filter algorithm
 *
 **/

#ifndef IMUSO3_H
#define IMUSO3_H


/* Function prototypes */
float invSqrt(float number);
void NonlinearSO3AHRSinit(float ax, float ay, float az, float mx, float my, float mz);
void NonlinearSO3AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float twoKp, float twoKi, float dt);
void IMUSO3Thread(void);

void TestForIMURot(void);

#endif

