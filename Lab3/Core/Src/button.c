/*
 * button.c
 *
 *  Created on: Sep 21, 2022
 *      Author: KAI
 */

#include "button.h"

int KeyReg0[4] = {SET,SET,SET,SET};
int KeyReg1[4] = {SET,SET,SET,SET};
int KeyReg2[4] = {SET,SET,SET,SET};
int KeyReg3[4] = {SET,SET,SET,SET};

int TimeOutForKeyPress =  500;
int button_flag[4] = {0,0,0,0};

int is_button_pressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	//TODO

	button_flag[index] = 1;
}

void getKeyInput(){
	for (int i=0;i<3;i++){
		  KeyReg2[i] = KeyReg1[i];
		  KeyReg1[i] = KeyReg0[i];
		  switch(i){
		  case 0:
			  KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
			  break;
		  case 1:
			  KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
			  break;
		  case 2:
			  KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
			  break;
		  default:
			  break;
		  }
		  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
		    if (KeyReg2[i] != KeyReg3[i]){
		      KeyReg3[i] = KeyReg2[i];

		      if (KeyReg3[i] == PRESSED_STATE){
		        TimeOutForKeyPress = 500;
		        subKeyProcess(i);
		      }
		    }else{
		       TimeOutForKeyPress --;
		        if (TimeOutForKeyPress == 0){
		          KeyReg3[i] = NORMAL_STATE;
		        }
		    }
		  }
		}
	}


