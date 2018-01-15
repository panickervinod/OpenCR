/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyUSB0" //Dynamixel on Serial3(USART3)  <-OpenCR

#define BAUDRATE  57600

DynamixelWorkbench dxl_wb;

void setup() 
{
  Serial.begin(57600);
  while(!Serial); // Open a Serial Monitor

  uint8_t scanned_id[16];
  uint8_t dxl_cnt = 0;
  uint8_t range = 100;

  dxl_wb.begin(DXL_BUS_SERIAL4, BAUDRATE);
  dxl_wb.scan(scanned_id, &dxl_cnt, range);

  if (dxl_cnt == 0)
    Serial.println("Can't find Dynamixels");

  for (int index = 0; index < dxl_cnt; index++)
    Serial.println("id : " + String(scanned_id[index]) + "   Model Name : " + String(dxl_wb.getModelName(scanned_id[index])));
  
}

void loop() 
{

}
