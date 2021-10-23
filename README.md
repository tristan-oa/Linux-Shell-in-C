# *<span style="color:#7c5295">Eggshell</span>*: A Linux Shell Written in C

This linux shell was developed as part of a programming assignment for the [CPS1012: Operating Systems and Systems Programming 1](https://www.um.edu.mt/courses/studyunit/CPS1012) course, forming part of my BSc Computer Science.

# The *<span style="color:#7c5295">Eggshell</span>* Interpreter

*Eggshell* is a command-line interpreter for the Linux OS. It was designed to cater for the following:

1. [**Shell Variables**](#shell-variables)
2. [**Internal and External Commands**](#internal-and-external-commands)
3. [**Input and Output Redirection**](#input-and-output-redirection)
4. [**Piping**](#piping)
5. [**Process Management**](#process-management)

These will be explained in the sub-sections to follow.


## <span style="color:blue">Shell Variables</span>

Shell variables are character strings to which a value is assigned. Shell variable names should be in UPPERCASE and can contain any of the following:

- letters ( **A-Z** )
- numbers ( **0-9** )
- underscores ( **_** )

*Eggshell* was designed to cater for these shell variables by default:

> <span style="color:#00719c">PATH</span>: The search path used to launch external commands

> PROMPT	- The string presented to the user to show that the shell is ready to accept
command input, e.g.	.

- CWD	- The current working directory; all file operations are relative to this path, e.g.
/home/student/cps1012 .

- USER	- The username of the current user, e.g.	.
- HOME	- The home directory of the current user, e.g.	.
- SHELL	- The shell of the current user; should be the absolute path of the eggshell
 

(vii) TERMINAL - The name of the terminal attached to the current eggshell session; for
 
(viii) EXITCODE	- The exit code returned by the last program run by the shell.

Note that variables unique to eggshell, such as TERMINAL or CWD, should be populated when the shell starts up.
(b)	A user should be allowed to modify the content of shell variables or create new ones by using
an assignment statement,	; for example:


(c)	Shared variables appearing as command arguments or on the right-hand side of an assign- ment are prefixed with a $; the shell should recognise these occurrences and perform textual replacement with the variable value:
 


## <span style="color:blue">Internal and External Commands</span>

as


## <span style="color:blue">Input and Output Redirection</span>

as


## <span style="color:blue">Piping</span>

asd


## <span style="color:blue">Process Management</span>

as






# Documentation

A detailed description of this project's deliverables can be found [here](https://github.com/tristan-oa/Python-DataStructures-Algorithms1-1st-year/blob/master/Assignment_SPECIFICATION.pdf).

A detailed technical documentation of the source code written can be found [here](https://github.com/tristan-oa/Python-DataStructures-Algorithms1-1st-year/blob/master/DOCUMENTATION.pdf).
