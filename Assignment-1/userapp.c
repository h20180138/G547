#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define DEVICE1 "/dev/adxl_x"
#define DEVICE2 "/dev/adxl_y"
#define DEVICE3 "/dev/adxl_z"

int convert(int);
char ch;
int main()  {
	int i,fd1,fd2,fd3,bin;
	unsigned int f;
	char ch,write_buf[100],read_buf[100];
	
	printf("Enter the choice\n x: Open adxl_x device\n y:Open adxl_y device\n z:Open adxl_z device\n");
	scanf("%c",&ch);
	
	switch(ch) {
	
	case 'x':{
		fd1 =open(DEVICE1, O_RDWR);
		if(fd1==-1){
			printf("file %s either doesn't exist or locked by other process",DEVICE1);
			exit(-1);
			}
		printf("Reading from the device adxl_x\n");
	
		read(fd1,read_buf,sizeof(read_buf));
		printf("the value of Rx is: ");
		for(i=0;i<10;i++){
		
		printf("%d",read_buf[i]);
		}
		
		close(fd1);
		break;
		}
	case 'y':{
		
		fd2 =open(DEVICE2, O_RDWR);
		if(fd2==-1){
			printf("file %s either doesn't exist or locked by other process",DEVICE2);
			exit(-1);
			}
		printf("Reading from the device adxl_y\n");
	
		read(fd2,read_buf,sizeof(read_buf));
		printf("the value of Ry is:");
		for(i=0;i<10;i++){
		
		printf("%d",read_buf[i]);
		}
		
		close(fd2);
		break;
		}
	case 'z':{
	
		fd3 =open(DEVICE3, O_RDWR);
		if(fd3==-1){
			printf("file %s either doesn't exist or locked by other process",DEVICE3);
			exit(-1);
			}
		printf("Reading from the device adxl_z\n");
	
		read(fd3,read_buf,sizeof(read_buf));
                printf("the value of Rz is:");
		for(i=0;i<10;i++){
		
		printf("%d",read_buf[i]);
		}
		
		close(fd3);
		break;
		}
	default:
		printf("Enter correct choice\n");
		break;	
}	
	return 0;
}
















