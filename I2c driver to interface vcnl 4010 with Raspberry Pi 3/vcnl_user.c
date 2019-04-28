/*This is the User Space code to generate System calls for VCNL 4010 proximity Sensor*/

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	
	int fileDesc;
	char *bus = "/dev/vcnl4010_sensor";
	if ((fileDesc = open(bus, O_RDWR)) < 0) 
	{
		//If the sensor is not connected 
		printf("Unable to load Bus. \n");
		
		exit(1);
	}

	//sending the slave address using IOCTL call 
	ioctl(fileDesc, I2C_SLAVE, 0x13); //VCNL4010 has a fixed slave address of 13h

	
	char data[4] ={0};

	if(read(fileDesc, data, 4) != 4)
	{
		printf("Unable to read file \n");
	}
	else
	{
		
		
		int proximity = (data[2] * 256 + data[3]);  //converting raw proximity values to digital values

		
		
		printf("The proximity value: %d \n", proximity);
	}

}

