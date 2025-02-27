

#include<stdlib.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>
#define MAX_TEXT 512
struct my_msg_st{
long int my_msg_type;
char some_text[MAX_TEXT];
};
int main()
{
int running=1;
struct my_msg_st some_data_bin;
struct my_msg_st some_data_oct;
struct my_msg_st some_data_hex;
int msgid;
char buffer[BUFSIZ];
msgid=msgget((key_t)1234,0666|IPC_CREAT);
if (msgid==-1) {
fprintf(stderr,"msgget failed with error: %d\n",errno);
exit(EXIT_FAILURE);
}
while(running){
printf("Enter the decimal no.: ");
fgets(buffer,BUFSIZ,stdin);
some_data_bin.my_msg_type=2;
some_data_oct.my_msg_type=8;
some_data_hex.my_msg_type=16;
if(strncmp(buffer,"end",3)!=0)
{
long long int octal;
//DEC TO OCTAL
int num=atoi(buffer);
int i=1;
while(num!=0) {
int rem=num%8;
num/=8;
octal+=rem*i;
i*=10;
}
sprintf(some_data_oct.some_text,"%lld",octal);
octal=0;
}
else{
strcpy(some_data_bin.some_text,buffer);
strcpy(some_data_oct.some_text,buffer);
strcpy(some_data_hex.some_text,buffer);
}
if(msgsnd(msgid,(void*)&some_data_bin,MAX_TEXT,0)==-1){
fprintf(stderr,"msgsnd failed\n");
exit(EXIT_FAILURE);
}
if(msgsnd(msgid,(void*)&some_data_oct,MAX_TEXT,0)==-1){
fprintf(stderr,"msgsnd failed\n");
exit(EXIT_FAILURE);
}
if(msgsnd(msgid,(void*)&some_data_hex,MAX_TEXT,0)==-1){
fprintf(stderr,"msgsnd failed\n");
exit(EXIT_FAILURE);
}
if(strncmp(buffer,"end",3)==0){
running=0;
}
}
exit(EXIT_SUCCESS);
}
