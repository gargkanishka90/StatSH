/* This source code is made by Kanishka Garg in CS 385 : Operating Systems at the University of Illinois at Chicago*/
/* This work is a part of course assignment HW1. Dated : 09/27/2013*/ 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int count_pipes(char []);
int CountTokens(char* );
void totaltime(double,double);

struct history{   // In order to make a history feature, a struct node is created and added to the list 
struct history* next;
char*** cmd;
double user_time;
double sys_time;
};
typedef struct history node;
node* first,*current;

void ShowList();//function to print timing stats using stats command
node * getnode();
void InsertAtStart(char***,double ,double );

int main(int count, char *command[]){//+1
char delimpipe[] = "|";
char delimspace[] = " ";
size_t k;
char* inp; 
struct rusage use;
//struct history* head;

first = NULL;

printf("--------------------------------------------------------------------------------------\n");

printf("*************************Welcome to STATsh - Shell redefined!*************************\n");

printf("---------------------------------------------------------------------------------------\n");

printf("-------------------------Created by : Kanishka Garg (kgarg3)----------------------------\n");

while(1){

printf("\n");
printf("Statsh:~$");

inp = (char*)malloc(1000*sizeof(char));
//printf("Enter the commands :");
getline(&inp, &k, stdin);
int kk = strlen(inp);
inp[kk-1] = '\0';
//gets(input);
int r = count_pipes(inp);// count the number of different commands users has put into the command line
//printf("The number of pipes are : %d\n",r);

if(strcmp(inp,"exit")==0)
{
 ShowList();
 exit(0);
}
else if(strcmp(inp,"stats")==0)
	{
	 ShowList();
	 //totaltime(total_user_time,total_system_time);
	}
	else if(strcmp(inp,"")==0)
	     {
		break;
		//printf("Empty command. Please enter something to continue");
	      }	
        else if(strcmp(inp,"\n")==0)
             { break; }



char **parseInput = NULL;
char ***parseCmd = NULL;

parseInput = (char**)malloc(r*sizeof(char));//allocate space for piped commands using malloc
parseCmd = (char***)malloc(r*sizeof(char));//allocate space for spaced command in one pipe using malloc

char* ptrTOpipe = NULL;
int i =0;

/* The code below will parse commands using "|" as a delimiter and separate it into different commands*/

ptrTOpipe = strtok(inp,delimpipe);
int fwd = 1;
while(ptrTOpipe!= NULL)
{     			
	parseInput[i++] = ptrTOpipe;
	ptrTOpipe = strtok(NULL,delimpipe);
	
}

for(i=0;i<r;i++)
{
//printf("The command number %d is : %s\n\n",(i+1),parseInput[i]);
}
/* The code below will break each parsed command into tokens so that we can get the command name as well as arguments for that particular command*/
int u =0;
while(u < r)
	{
		char* after = NULL;
		int j =0;int y=0;
		int token_count = CountTokens(parseInput[u]);
		parseCmd[u] = (char**)malloc(token_count * sizeof(char));
		after = strtok(parseInput[u], delimspace);
		while(after!=NULL)
		{
		parseCmd[u][j++] = after;
		//printf("PARSECOMMAND : %s\n",after);
		after = strtok(NULL, delimspace);
		}
		parseCmd[u][token_count] = NULL;
		u++;
	}
		parseCmd[r] = NULL;

				/* Forking off child code*/		
				int chd_pid[r];
				int p[2];// create new file descriptors
				int next =0;
				int status = -1;
				int cur =0;
				double u_time,s_time;
				double total_user_time = 0.000;
				double total_system_time = 0.000;
				while(*parseCmd!=NULL)
				{
				pipe(p);
				int temp = fork();
				int chd_pid[cur];
				chd_pid[cur] = temp;
				switch (chd_pid[cur]) 
			 	{ 
			 	case 0: 
				//printf("Yeah, I'm born and I'm child no. %d\n",(cur+1));
				dup2(next, 0); //change the input according to the old one 
			  	if (parseCmd[1] != NULL)
			    	{ dup2(p[1], 1);}
			  	close(p[0]);
			  	execvp(parseCmd[cur][0], parseCmd[cur]);
			  	//printf("*********************ERROR*****************");
				exit(0);
				
				default: 
				{
				wait4(temp,&status,0,&use);
				getrusage(temp,&use);
				u_time = (double)use.ru_utime.tv_sec*(1000000) + (double)use.ru_utime.tv_usec / 1000000;
				s_time = (double)use.ru_stime.tv_sec*(1000000) + (double)use.ru_stime.tv_usec / 1000000;
				//total_user_time+ = u_time;
				//total_system_time+ = s_time;
				printf("_________________________________________________________________________\n");
				printf("The time stats for %s are \n 1. User Time : %.3f and \n 2. System Time : %.3f\n \n",**parseCmd,u_time,s_time);
				printf("_________________________________________________________________________\n");
				InsertAtStart(parseCmd,u_time,s_time);
				close(p[1]);
			  	next = p[0]; //save the input for the next command
			  	parseCmd++;
				break;
				}

			 	case -1: 
			 	perror("fork"); 
				exit(1); 
				}
				}
				//ShowList();
				//totaltime(total_user_time,total_system_time);
				
}
return 0;
}

void InsertAtStart(char***cmds,double ut,double st)// to make a linked list of history of commands.  
{   
 node *temp;   
 temp = getnode();   
 temp->cmd = cmds;
 temp->user_time = ut;
 temp->sys_time = st;   
 temp->next = NULL;   
 if (first == NULL)   
    first = temp;   
 else   
 {   
  temp->next = first;   
  first = temp;   
  }   
}   

node * getnode()   
{   
 node * temp;   
 temp = (node *) malloc(sizeof(node));   
 return(temp);   
}   

void ShowList()   
{   
  current = first;   
 //if (current == NULL)   
   // printf("\aThere are no nodes in the Linked List.\n");   
 while (current != NULL)   
 {   
  printf("The command is %s\n",**(current->cmd));
  printf("--------------------------------------------------------------\n");
  printf(" User Time elapsed : %.3f\n",(current->user_time));
  printf(" System Time elapsed : %.3f\n\n",(current->sys_time));
  printf("--------------------------------------------------------------\n");	
  current = current->next;   
  }   
}   

void totaltime(double a,double b)
{
  printf("--------------------------------------------------------------\n");
  printf(" Total User Time elapsed : %.3f\n",a);
  printf(" Total System Time elapsed : %.3f\n\n",b);
  printf("--------------------------------------------------------------\n");
}
	
			
		
		/* This function calculates the no. of commands given by the user*/		
		int count_pipes(char p[]){
		int count;
		int i=0;
			while(p[i]!='\0')
			{
			 if(p[i] == '|'){
			count++;
			}
			i++;
			}
			return (count+1);
		}
		
		/* tHis function calculates the no. of tokens inputed by the user*/
		int CountTokens(char * input)
		{
		char * nxt = input;
		int words = 0, i = 0;
		while(nxt[i] != '\0')
		{
		if(nxt[i] == ' ' || nxt[i+1] == '\0')
		words++;
		i++;
		}

		return words;
		}

