#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "walkingdriver/driver.h"



void W();
void A();
void S();
void D();
void Raise();
void Lower();

void endCallback()
{
	printf("I moved !\n");
}

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;dw
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }


int main(){
    int c;
    initAX12(115200);
    FILE *file;
    file = fopen("logo.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
    fclose(file);
    }
    printf("\n");
    AX12move(121, 0, &endCallback);

    while ((c = getch()) != '.'){
        switch(c){
            case 'w':
                W();
                break;
            case 'a':
                A();
                break;
            case 's' :
                S();
                break;
            case 'd':
                D();
                break;
        }
    }

}

void W(){
    printf("You pressed W\n");
    uint8_t id = 164;
    AX12setMode(id, WHEEL_MODE);
    double speed = 70;
    double torque = 50;

    AX12turn(id, speed);

}
void A(){
    double posMax = 15;
    printf("You pressed A\n");
    uint8_t id = 121;
    double speed = -5;
	double torque = 50;
	AX12setTorque(id, torque);
	AX12setSpeed(id, speed);
    double position = AX12getPosition(id);
    if(position-5 > -1*posMax)
        AX12move(id, ((int)position-5 ) %100, &endCallback);

}
void S(){
    printf("You pressed S\n");
}
void D(){
    printf("You pressed D\n");
    double posMax = 15;
    uint8_t id = 121;
    double speed = 5;
	double torque = 50;
	AX12setTorque(id, torque);
	AX12setSpeed(id, speed);
    double position = AX12getPosition(id);
    if(position+5 < posMax)
        AX12move(id, ((int)position+5 ) %100, &endCallback);
}
