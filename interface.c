#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void W();
void A();
void S();
void D();
void Raise();
void Lower();

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
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }


int main(){
    int c;
    FILE *file;
    file = fopen("logo.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
    fclose(file);
    }
    printf("\n");

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
}
void A(){
    printf("You pressed A\n");
}
void S(){
    printf("You pressed S\n");
}
void D(){
    printf("You pressed D\n");
}
