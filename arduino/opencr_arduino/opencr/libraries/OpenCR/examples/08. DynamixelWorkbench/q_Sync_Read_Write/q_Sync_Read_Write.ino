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

uint8_t dxl_id[2] = {1, 2};
uint8_t dxl_cnt = 2;

int32_t goal_position[2] = {1000, 3000};

int32_t present_position[2] = {0, 0};
int32_t present_velocity[2] = {0, 0};

void setup() 
{
  Serial.begin(57600);
  while(!Serial); // Open a Serial Monitor  

  dxl_wb.begin(DXL_BUS_SERIAL4, BAUDRATE);

  for (int cnt = 0; cnt < dxl_cnt; cnt++)
  {
    dxl_wb.ping(dxl_id[cnt]);
    dxl_wb.jointMode(dxl_id[cnt]);
  }

  dxl_wb.addSyncWrite("Goal_Position");
  dxl_wb.addSyncRead("Present_Position");
  dxl_wb.addSyncRead("Present_Velocity");
}

void loop() 
{  
  dxl_wb.syncWrite("Goal_Position", goal_position);

  do
  {
    int32_t *get_data;

    get_data = dxl_wb.syncRead("Present_Velocity");
    for (int cnt = 0; cnt < dxl_cnt; cnt++)
      present_velocity[cnt] = get_data[cnt];

    get_data = dxl_wb.syncRead("Present_Position");
    for (int cnt = 0; cnt < dxl_cnt; cnt++)
      present_position[cnt] = get_data[cnt];

    log();
  }while(abs(goal_position[0] - present_position[0]) > 20 && 
         abs(goal_position[1] - present_position[1]) > 20);

  swap();
}

void log()
{
  for (int cnt = 0; cnt < dxl_cnt; cnt++)
  {
    Serial.print("[ ID : "    + String(dxl_id[cnt])           +
                 " GoalPos: " + String(goal_position[cnt])    + 
                 " PresPos: " + String(present_position[cnt]) +
                 " PresVel: " + String(present_velocity[cnt]) + 
                 " ]  ");
  }
  Serial.println("");
}

void swap()
{
  int32_t tmp = goal_position[0];
  goal_position[0] = goal_position[1];
  goal_position[1] = tmp;
}