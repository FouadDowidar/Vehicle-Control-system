/******************************************************************************
 *
 * Module: Vehicle Control system
 *
 * File Name: project1.c
 *
 * Description: Source file for Vehicle Control system Project
 *
 * Author: Fouad Dowidar
 *
 *******************************************************************************/

#include<stdio.h>
#include"project1.h"

int main(void){

	/*for control over the buffering strategy and buffer size.*/
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/*calling main menu function.*/
	main_menu();

	return 0;
}

/*for printing the main menu to the screen*/
void main_menu(void){
	char c;
	do{
		printf("|||||||||||||||||||||||||||||||||||||\n"
				"||a. Turn on the vehicle engine    ||\n"
				"||b. Turn off the vehicle engine   ||\n"
				"||c. Quit the system               ||\n"
				"|||||||||||||||||||||||||||||||||||||\n");

		/*getting input character from the user.*/
		scanf(" %c",&c);

		/*checking the character for decision to make.*/
		if(c=='c'||c=='C')
		{
			printf("Quit the system\n");
			return;
		}
		else if(c=='b'||c=='B')
		{
			printf("Turn off the vehicle engine\n");
			main_menu();
		}
		else if(c=='a'||c=='A')
		{
			printf("Turn on the vehicle engine\n");
			Sensors_set_menu();
		}
		else
		{
			printf("error invalid character \n"
					"going back to main menu\n");
			c='f';
		}
	}while(c=='f');
}

/*for printing the sensor menu to the screen*/
void Sensors_set_menu(void){
	char c;

	/*Static variables have a property of preserving their value.
	static inital value=0*/
	static int vehicle_speed;
	static float r_temperature;
	static float e_temperature;
	static int AC;
	static int Controller;

	do{

#if WITH_ENGINE_TEMP_CONTROLLER==1
		printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
				"||a. Turn off the engine                                      ||\n"
				"||b. Set the traffic light color                              ||\n"
				"||c. Set the room temperature (Temperature Sensor)            ||\n"
				"||d. Set the engine temperature (Engine Temperature Sensor)   ||\n"
				"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");

#else
		printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
				"||a. Turn off the engine                                      ||\n"
				"||b. Set the traffic light color                              ||\n"
				"||c. Set the room temperature (Temperature Sensor)            ||\n"
				"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
#endif

		/*getting input character from the user.*/
		scanf(" %c",&c);

		/*checking the character for decision to make.*/
		if(c=='a'||c=='A')
		{
			printf("Turn off the engine\n");

			/*calling back the main menu function*/
			main_menu();

		}
		else if(c=='b'||c=='B')
		{

			/*passing by reference the vehicle speed
			  to traffic light data function*/
			traffic_light_data(&vehicle_speed);

			if(vehicle_speed==30)
			{
				AC=ON;
				r_temperature=(r_temperature*1.25) + 1.0;

#if WITH_ENGINE_TEMP_CONTROLLER==1
				Controller=ON;
				e_temperature=(e_temperature*1.25) + 1.0;
#endif
			}

			/*passing by reference all state of vehicle
			  to vehicle state function*/
			vehicle_state(&AC,&vehicle_speed,&r_temperature,&Controller,&e_temperature);

			/*calling back sensors set menu function*/
			Sensors_set_menu();

		}
		else if(c=='c'||c=='C')
		{
			printf("Enter the required room temperature\n");

			/*passing by reference the room temperature and AC
			  to room temperature function*/
			room_temperature(&r_temperature,&AC);

			/*passing by reference all state of vehicle
			  to vehicle state function*/
			vehicle_state(&AC,&vehicle_speed,&r_temperature,&Controller,&e_temperature);

			/*calling back sensors set menu function*/
			Sensors_set_menu();

		}
#if WITH_ENGINE_TEMP_CONTROLLER==1
		else if(c=='d'||c=='D')
		{

			printf("Enter the required engine temperature\n");

			/*passing by reference the engine temperature and Controller
			  to enginge temperature function*/
			engine_temperature(&e_temperature,&Controller);

			/*passing by reference all state of vehicle
			  to vehicle state function*/
			vehicle_state(&AC,&vehicle_speed,&r_temperature,&Controller,&e_temperature);

			/*calling back sensors set menu function*/
			Sensors_set_menu();
		}
#endif
		else
		{
			printf("error invalid character \n"
					"going back to Sensors set menu\n");
			c='f';
		}
	}while(c=='f');
}

/*to set the vehicle speed based on the traffic light color*/
void traffic_light_data(int *v_speed){
	char c;
	do{
	printf("Enter the required color\n");

	/*getting input character from the user.*/
	scanf(" %c",&c);

	/*checking the character for decision to make.*/
	if(c=='G'||c=='g')
	{*v_speed=100;}
	else if(c=='O'||c=='o')
	{*v_speed=30;}
	else if(c=='R'||c=='r')
	{*v_speed=0;}
	else
	{
		printf("error invalid character \n"
				"going back to traffic light\n");
		c='f';
	}

	}while(c=='f');
}

/*to control the AC based on room temperature*/
void room_temperature(float *room,int *ac)
{
	float room_temperature;

	/*getting room_temp number from the user.*/
	scanf("%f",&room_temperature);

	/*checking number for decision to make.*/
	if((10>room_temperature)||(30<room_temperature))
	{
		*ac=ON;
		*room=20.0;

	}
	else
	{
		*ac=OFF;
	}
}

#if WITH_ENGINE_TEMP_CONTROLLER==1

/*to control the Controller based on engine temperature*/
void engine_temperature(float *engine,int *controller)
{
	float engine_temp;

	/*getting engine_temp number from the user.*/
	scanf("%f",&engine_temp);

	/*checking number for decision to make.*/
	if((100>engine_temp)||(150<engine_temp))
	{
		*controller=ON;
		*engine=125.0;
	}
	else
	{
		*controller=OFF;
	}
}
#endif

/*Printing all the vehicle status after each operation*/
void vehicle_state(int *ac,int *ve_speed,float *roomt,int *con,float *enginet)
{
	/*Printing all the vehicle status after each operation*/
	printf("Engine is ON\n");

	if(*ac==ON)
	{printf("AC is ON\n");}
	else if(*ac==OFF)
	{printf("AC is OFF\n");}

	printf("Vehicle Speed: %d Km/Hr\n",*ve_speed);

	printf("Room Temperature: %f C\n",*roomt);

    #if WITH_ENGINE_TEMP_CONTROLLER==1

	if(*con==ON)
	{printf("Engine Temp Controller is ON\n");}
	else if(*con==OFF)
	{printf("Engine Temp Controller is OFF\n");}

	printf("Engine Temperature: %f C\n",*enginet);

    #endif
}
