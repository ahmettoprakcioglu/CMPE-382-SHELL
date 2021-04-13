# CMPE 382 SHELL PROJECT #1

Group Members:</br>
Ahmet Kaan Toprakçıoğlu</br>
Tanercan Altuntaş 


## HOW TO RUN?

In which mode would you like to run it first?</br>
Interactive mode: It will be enough to follow the commands in below.

`./MAKEFILE`</br>
`./shell`</br>	  

Batch mode: It will be enough to follow the commands in below.

`./MAKFILE`</br>
`./shell batch.bat`</br>
   
If the user enters the wrong batch file name, the program sends an error message and continues in interactive mode.

## DESIGN OVERVIEW

Our shell works in 2 different modes. These are batch mod and interactive mod. In interactive mode, if the program does not contain semicolons and pipe characters in the input, it sends the input directly to the system function. On the other hand, the input contains only the pipe character. In this case, the input is parsed from the parts with the pipe characters. Then, each command that is parsed is sent to the system function in order. In our program, if the input contains a semicolon and a pipe character, two different cases will arise.

The first case is that the input contains only semicolon characters. In this case, the input is parsed according to the semicolon character. Separated inputs are sent to this function by creating a thread function. Thus, the output given by the program appears to the user as intermixed.

The other case is that the input contains both semicolons and the pipe character. In this case, the input is first parsed according to the pipe character. Then, it is checked whether each of the parsed inputs contains semicolons. If it contains, the parsed input is parsed according to the semicolon character. In this situation, the separation process takes place twice. The inputs parsed for the second time (parsed according to the semicolon character) are sent to the thread function.


In the batch mode, each line of the batch file we have created is read by the program and its output is printed on the screen. After the reading process is completed, if the batch file does not contain the "quit", the program automatically switches to interactive mode. If it contains the "quit", the program ends.

## COMPLETE SPECIFICATION

Some commands running in our program cause errors in the bash shell. These commands are listed below.</br></br>
`;;;ls -l ;; pwd`</br>
`; ls -l ; cat text1 ; cat text2`</br>
`ls ||| | cat text1 ;; pwd`</br>
`cat text1 ; ; grep text1File cat text1`</br></br>
More than one semicolon or pipe character is ignored in the commands mentioned above. Whether the first character of the input is a semicolon or a pipe is ignored. In addition, the spaces between ignored characters are ignored and do not cause any errors.

## BUGS OR PROBLEMS

In a shell, system() executes a command. That shell is a new process. For the shell process in which it is run, the cd command changes the current directory. This is inherited to the shell's child processes. However, it has no effect on the parent processes' current directory. That's why the “cd” command does not work in our program. Also, commands that are not in the bash shell do not work in our program and sends an error message.

