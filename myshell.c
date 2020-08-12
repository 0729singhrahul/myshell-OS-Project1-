/*
Rahul Singh 
Raufil Dhuka
*/


#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
/*All the basic variables declared*/

char buffer[100];
char *p;
char *args[10];
int last=0;
int count=0;
int pid;
int commands=0;

while(1)
{

	//printf("myShell>");
	//readin the shell line for commands 
	fgets(buffer,sizeof(buffer),stdin);
	buffer[strlen(buffer)-1]=NULL;

	//checking if the input commands is exit if so the program 
	//terminates thus ending the program myShell.c and prints the 
	//number of commands executing before printing
	if(strcmp(buffer,"exit") == 0)
	{

		printf("Number of commands executed: %d ",commands);
		printf("Exiting... ");
		exit(0);
	}

	//allocating memory for the arguments array 
	for(int i = 0; i < 10; i++)
	{
		args[i] = (char*)malloc(20*sizeof(char));
	}

	//splitting the input command(buffer) based on white
	//space and then copying it to the arguments array
	p=strtok(buffer," ");
	strcpy(args[count++],p);
	while(p!=NULL)
	{
		p = strtok(NULL," ");
		if(p == NULL)
		{
			break;
		}
		strcpy(args[count++],p);

	}


	//updating the args array and using the fork 
	//function to create a child 
	args[count]=NULL;
	pid = fork();
	
	
	if(strcmp(buffer,"exit") == 0)
	{

		printf("Number of commands executed: %d ",commands);
		exit(0);
	}

	//child part

	if(pid == 0) 
	{	//check if there is & at the end and the execute the 
		//command accordingly 
		if ((strcmp(args[count-1],"&")==0))
		{	
			args[count-1]=NULL;
			
			execvp(args[0],args);
			args[count-1]="&";
			
		}
		else{
			execvp(args[0],args);
		}
		//in case there are any errors while executing the command
		perror("Command not executed by child. ");
		printf("After execvp failed ");
		exit(0);
	}

	//parent part
	else 
	{	//printing the pid of the child for & symbol at the end
		if ((strcmp(args[count-1],"&")==0))
		{	printf("The PID of the child is %d\n",pid);
			
		}
		//waiting if no & symbol at the end
		else{
			wait(NULL);}
		
		//update other varibles which is common for both parts
		commands++;
		
		if(strcmp(buffer,"exit") == 0)
		{
			printf("Number of commands executed: %d ",commands);
			exit(0);

		}

		buffer[0]=NULL;
		count=0;
		*args=NULL;

	}

fflush(stdin);
}
return 0;
}

