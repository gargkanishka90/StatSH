Author: Kanishka Garg ( UIN : 675005799 )
        ACCC account name : kgarg3

Size of statsh.c : 6.56KB

Steps to run:

cs.bert..@uic.edu:~$ gcc statsh.c -o statsh
cs.bert..@uic.edu:~$ ./statsh

Features supported by STATsh:

1. Basic commands like ls,date,who,ps,pstree etc.
   Eg:
   Statsh:~$ ps
     PID  TTY        TIME  CMD
     3076 pts/0    00:00:00 bash
     3212 pts/0    00:00:00 statsh
     3213 pts/0    00:00:00 ps

2. If a user types "stats" in the command-line argument of STATsh, then the timing resource usage will 
   come on the command-line in the following format :

   ----------------------------------------------------------------------------------------
   The command is "command-name"
   ----------------------------------------------------------------------------------------
   User Time elapsed : 0.004
   System Time elapsed : 0.016

   -----------------------------------------------------------------------------------------
   
   ----------------------------------------------------------------------------------------
   The command is "command-name"
   ----------------------------------------------------------------------------------------
   User Time elapsed : 0.004
   System Time elapsed : 0.016

   -----------------------------------------------------------------------------------------

   _________________________________________________________________________________________
   The time stats for stats are
   1. User Time : 0.000 and
   2. System Time : 0.000
   
   _________________________________________________________________________________________

3. After every command(or piped command) the user executes on the command-line interface, timing usage 
   statistics for each command will come on the command-line with the output of the last command.
   For eg :
   statsh:~$date
   
   Fri Sep 27 02:49:35 CDT 2013	

   ----------------------------------------------------------------------------------------
   The command is date
   ----------------------------------------------------------------------------------------
   User Time elapsed : 0.004
   System Time elapsed : 0.016

   -----------------------------------------------------------------------------------------

4. STATsh supports the feature of piped command as in normal unix-like shell.For eg : ls -lrt|ps|date etc.

5. If "exit" is typed then default shell will come back.

6. If " " is typed then STATsh will prompt again.


Features NOT-SUPPORTED by STATsh:

1. file I/O redirection.
2. No option of background processes.

References : 
Programming in Ansi C 4e by BALAGURUSWAMY ( For Linked List Implementation )








   




