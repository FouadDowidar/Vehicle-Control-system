/******************************************************************************
 *
 * Module: Vehicle Control system
 *
 * File Name: project1.h
 *
 * Description: Header file for Vehicle Control system Project
 *
 * Author: Fouad Dowidar
 *
 *******************************************************************************/

#ifndef PROJECT1_H_
#define PROJECT1_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*when WITH_ENGINE_TEMP_CONTROLLER = 1
 all engine temperature and controller code are excuted
 else they won't compile*/
#define WITH_ENGINE_TEMP_CONTROLLER 1


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

enum status
{
	OFF,ON              /*OFF=0,ON=1*/
};

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*for printing the main menu to the screen*/
void main_menu(void);

/*for printing the sensor menu to the screen*/
void Sensors_set_menu(void);

/*to set the vehicle speed based on the traffic light color*/
void traffic_light_data(int *v_speed);

/*to control the AC based on room temperature*/
void room_temperature(float *room,int *ac);

/*to control the Controller based on engine temperature*/
void engine_temperature(float *engine,int *controller);

/*Printing all the vehicle status after each operation*/
void vehicle_state(int *ac,int *ve_speed,float *roomt,int *con,float *enginet);

#endif /* PROJECT1_H_ */
