/*                      PRE-PROCESSOR DIRECTIVES                       */


/* Including a number of header files associated to certain functions
 * used in the code below */

/* The stdio.h library consists of the standard input and output operations
 * used: printf(), perror(), sprintf(), putchar(), FILE, stdin, stdout
 * fopen(), fprintf(), fgets(), fclose() */
#include <stdio.h>

/* the stdlib.h library defines 4 different variable types together with
 * macros and multiple functions which perform general operations
 * The ones used are : NULL, getenv(), setenv(), exit() EXIT_FAILURE, atoi */
#include <stdlib.h>

/* the string.h library defines multiple functions dealing with arrays of
 * characters. The particular ones used here are: strtok(), strlen(),
 * strstr(), strcmp(), strcat(), memset() */
#include <string.h>

/* the unistd.h library consists of system call wrapper functions and other
 * miscellaneous functions which grant access to the POSIX OS API
 * The ones used in this program are: isatty(), ttyname(), chdir(),
 * getcwd(), fork(), execvp(), close(), dup(), dup2(), STDIN_FILENO,
 * STDOUT_FILENO, STDERR_FILENO, pipe() */
#include <unistd.h>

/* the dirent.h library consists of functions which specify the format
 * of directory entries. The ones used include: DIR, opendir(), closedir() */
#include <dirent.h>

/* the sys/wait.h header defines certain declarations for waiting
 * The only one used in this program is: waitpid() */
#include <sys/wait.h>

/* the sys/stat.h header stores dat related to the stat() function
 * This header was recommended to be included alongside sys/wait.h */
#include <sys/stat.h>

/* the fcntl.h library defines file control operations for use by fcntl()
 * and open() functions. Apart from the open() function used, flags
 * in this program include: O_WRONLY, O_CREAT, O_TRUNC, O_APPEND, O_RDONLY */
#include <fcntl.h>

/* the errno.h library defines the integer macro errno which is
 * used when setting the exitcode when an error occurs */
#include <errno.h>

/* the signal.h library defines several macros to handle different signals
 * In the case of this program, the  SIGINT signal was handled */
#include <signal.h>

/* the signal.h library defines 4 macros for a Boolean datatype out of which
 * 'true' is used in this assignment */
#include <stdbool.h>

/* the linenoise header file is a readline replacement library which
 * makes managing of user input easier. It also offers functions which
 * were also implemented in this project which take care of history
 * handling and line completion */
#include "linenoise.h"

// Defining a macro for the maximum size of arguments to be accepted
#define MAX_ARGS 255



/*                         FUNCTION PROTOTYPES                       */


/* A void function which splits a given string into arguments.
 * This takes 2 parameters, the string (2nd parameter) yet to
 * be split into arguments which are then stored into args (1st
 * parameter). This function does not return anything*/
void run(char **args, char *string);

/* An integer function which adds another 3 variables to the list of
 * enviromental variables. These are: PROMPT, CWD & TERMINAL
 * This function returns 0 on success and -1 on failure */
int init_shell_vars(char **argv);

/* A void function which sets the EXITCODE returned by the last
 * program run by the shell. This is the last shell variable set and
 * is updated each time an operation runs on the shell
 * Nothing is returned back */
void set_exitcode(int function);

/* A void function which sets the EXITCODE for whenever a function
 * returns back through EXIT_FAILURE
 * This function does not return anything back */
void set_exit_when_fail();

/* An int function which creates a new shell variable based on
 * what the user enters and if it already exists, it appends it
 * This has 2 parameters, the name of the shell variable to be
 * created as the 1st and the value to be stored in it as the 2nd
 * This function returns 0 on success and -1 on failure */
int create_shell_var(char *name, char *value);

/* A void function which exits the shell.
 * This function does not return anything back */
void int_exit();

/* An int function which prints out whatever the user enters
 * This can also obtain values of shell variables.
 * This has the arguments entered by the user passed as parameters
 * This function returns 0 on success and -1 on failure*/
int int_print(char **args);

/* An int function which changes the current working directory
 * These changes can also be seen when printing the value in CWD
 * This has the arguments entered by the user passed as parameters
 * This function returns 0 on success and -1 on failure */
int int_chdir(char **args);

/* An integer function which simply prints out all the shell vars
 * This function returns 0 on success and -1 on failure*/
int int_all();

/* An int function which reads runs commands found in a given file
 * This has the arguments entered by the user passed as parameters
 * This function returns 0 on success and -1 on failure*/
int int_source(char **args);

/* A linenoise void function which automatically completes internal
 * commands when user hits tab
 * This function does not return anything back*/
void completion(const char *buf, linenoiseCompletions *lc);

/* An int function which checks the input entered by the user and
 * returns the appropriate command back.
 * This checks for redirection followed by all the internal commands,
 * followed by checks for piping and finally checks for external commands
 * This has the arguments entered by the user passed as parameters*/
int check_input(char **args);

/* An int function which forks to execute an external command.
 * This has the arguments entered by the user passed as parameters*/
int external(char **args);

/* An int function which implements the '>' redirect operator
 * Both stdout and stderror of the command entered are redirected
 * to a file as specified by the user
 * This has the arguments entered by the user passed as the 1st
 * parameter and the position i of the '>' redirect operator in
 * the args as the 2nd
 * This function returns 0 on success and -1 on failure */
int forward_1_arrow(char **args, int i);

/* An int function which implements the '>>' redirect operator
 * Like the previous function, both stdout and stderror are
 * redirected to a file as specified by the user with the difference
 * that each time, contents added are appended to the file as opposed
 * to overwriting everything
 * This has the arguments entered by the user passed as the 1st
 * parameter and the position i of the '>>' redirect operator in
 * the args as the 2nd
 * This function returns 0 on success and -1 on failure */
int forward_2_arrows(char **args, int i);

/* An int function which implements the '<' redirect operator
 * In this function, the stdin is redirected from a file to a function
 * as specified by the user
 * This has the arguments entered by the user passed as the 1st
 * parameter and the position i of the '<' redirect operator in
 * the args as the 2nd
 * This function returns 0 on success and -1 on failure */
int back_1_arrow(char **args, int i);

/* An int function which implements the '<<<' redirect operator
 * In this function, the stdin is redirected from a 'here string'
 * to a function as specified by the user
 * This has the arguments entered by the user passed as the 1st
 * parameter and the position i of the '<<<' redirect operator in
 * the args as the 2nd
 * This function returns 0 on success and -1 on failure */
int back_3_arrows(char **args, int i);

/* An int function which implements the pipe operator for single
 * and multiple pipe cases respectively
 * Based on the number of pipes found as entered by the user, a
 * number of processes are forked to be able to redirect output
 * (write end) from the parent into a pipe into the input (read
 * end) of the child.
 * This has the arguments entered by the user passed as the 1st
 * parameter and the number of '|' operators detected
 * the args as the 2nd*/
int piping(char **args, int pipecount);

/* A void function which catches the SIGINT signal and handles it
 * so that the command line does not quit abruptly when ctrl + C
 * is pressed and instead, the signal is forwarded to the process
 * currently running
 * This function does not return anything back */
void sigint_handler(int signal);


/*                    GLOBAL SCOPE VARIABLES / ARRAYS                */


/* A global array of all the redirect operators implemented */
char *ops[] = {
        ">",
        ">>",
        "<",
        "<<<'"
};

/* A global array of function pointers which point to the
 * corresponding functions based on the redirect operator entered */
int (*ops_address[])(char **, int) = {
        &forward_1_arrow,
        &forward_2_arrows,
        &back_1_arrow,
        &back_3_arrows

};


/*                         MAIN FUNCTION                       */


/* The main function having the number of arguments passed as the
 * 1st parameter and the actual arguments as the 2nd */
int main(int argc, char **argv) {

    /* A call to the functions which create the remaining 4 shell
     * variables unique to the eggshell as required
     * The return value of the init_shell_vars() function
     * determines the value the EXITCODE shell var will have*/
    set_exitcode(init_shell_vars(argv));

    /* Stores user input as a string*/
    char *line;

    /* Stores user input as separate arguments delimited by " "*/
    char *args[MAX_ARGS];

    /* Stores return value of the function which checks what needs
     * to be done with the input to provide the user with
     * appropriate output */
    int return_val;

    /* A builtin linenoise function that accesses a file which
     * temporarily contains a record of the already inserted lines
     * of text and loads it */
    linenoiseHistoryLoad("history.txt");

    /* Another builtin linenoise function which allows for the
     * completion of internal commands upon hitting tab*/
    linenoiseSetCompletionCallback(completion);

    /* A call to the function handling the SIGINT signal */
    signal(SIGINT, sigint_handler);

    /* A while loop which provides the user with a PROMPT for
     * entering commands. This keeps listening until the user
     * enters text. When text is entered, it is processed*/
    while (true) {

        /* Text entered by user is stored in line */
        line = linenoise(getenv("PROMPT"));

        /* Handles the case in which null is returned */
        if (line == NULL) {
            printf("Ctrl-C\n");
            linenoiseFree(line);
            continue;
        }

        /* Handles the case in which user hits 'Enter' without any commands */
        if (strlen(line) == 0) {
            continue;
        }

        /* A linenoise function which appends an inserted
         * command to the list of inserted commands */
        linenoiseHistoryAdd(line);

        /* A function which separates the inserted string
         * entered by the user into arguments and stores
         * them in an arguments array */
        run(args, line);

        /* These arguments are then passed to a function which
         * identifies the command entered and the return value
         * returned is stored in the placeholder return_val */
        return_val = check_input(args);

        /* The EXITCODE is set based on the value returned */
        set_exitcode(return_val);

    }
    /* The previously allocated memory for the line is now freed */
    linenoiseFree(line);


    /* Return value of main function */
    return 0;
}


/*                        ALL OTHER FUNCTIONS                        */


/* run() function starts here */
void run(char **args, char *string) {

    /* Defining of variables and setting pointer to NULL */
    char *token = NULL;
    int tokenIndex;

    /* Gets the first token delimited by " " */
    token = strtok(string, " ");

    /* Loops through all string and separates into args */
    for (tokenIndex = 0;
         token != NULL && tokenIndex < MAX_ARGS - 1;
         tokenIndex++) {
        args[tokenIndex] = token;
        token = strtok(NULL, " ");
    }

    /* sets last token to NULL */
    args[tokenIndex] = NULL;

}


/* init_shell_vars() function starts here */
int init_shell_vars(char **argv) {

    /* Creates shell variable PROMPT and handles errors if unsuccessful */
    if (setenv("PROMPT", ">>> ", 1) == -1) {
        perror("Error when setting PROMPT");
        return -1;
    }


    /* Creates shell variable CWD and handles errors if unsuccessful */

    /* Gets environmental variable PWD and stores in char pointer */
    char *dirname = getenv("PWD");

    /* Opens directory obtained */
    DIR *dir = opendir(dirname);

    /* If directory exits this section runs */
    if (dir) {

        /* Opened directory is closed */
        closedir(dir);

        /* The CWD shell var in set with error checking included */
        if (setenv("CWD", dirname, 1) == -1) {
            perror("Error when setting CWD ");
            return -1;
        }

        /* If directory does not exist, user is infromed
         * through an error message and function returns -1*/
    } else {
        perror("Error when locating specified dir ");
        return -1;
    }


    /* Creates shell variable TERMINAL and handles errors if unsuccessful */

    /* Converts the first argv element to an integer and stores in fd */
    int fd = atoi(argv[0]);

    /* If the value of fd is actually a terminal, this section runs */
    if (isatty(fd)) {

        /* terminal name of existing terminal is stored */
        char *tname = ttyname(fd);

        /* TERMINAL shell var is set and error checking is performed */
        if (setenv("TERMINAL", tname, 1) == -1) {
            perror("Error when setting TERMINAL");
            return -1;
        }

        /* If fd does not store existing terminal info, user is informed
         * with an error and program execution returns to main with -1*/
    } else {
        perror("Error when checking if terminal exists");
        return -1;
    }

    /* If all 3 assignments were successful, 0 is returned back */
    return 0;

}


/* set_exitcode() function starts here */
void set_exitcode(int function) {

    /* A temp character array is initialised */
    char temp[10];

    /* The value of errno is assigned to the temp array */
    sprintf(temp, "%d", errno);

    /* If return value of previous function is 0, this code runs */
    if (function == 0) {

        /* EXITCODE set to 0 and error checking is performed */
        if(setenv("EXITCODE", "0", 1) == -1){
            perror("setenv() fail");
            EXIT_FAILURE;
        }

        /* if return value is -125, run this part */
    } else if (function == -125) {

        //do nothing

        /* if return value is not 0 nor -125, run this part */
    } else {

        /* EXITCODE set to errno value and error checking is performed */
        if(setenv("EXITCODE", temp, 1) == -1){
            perror("setenv() fail");
            EXIT_FAILURE;
        }
    }

}


/* set_exit_when_fail() function starts here */
void set_exit_when_fail() {

    /* errno value is stored in a temp string */
    char temp[10];
    sprintf(temp, "%d", errno);

    /* EXITCODE is then set to the value of errno and error checking is done */
    if(setenv("EXITCODE", temp, 1) == -1){
        perror("EXITCODE not set");
    }

}


/* create_shell_var() function starts here */
int create_shell_var(char *name, char *value) {

    /* Shell var as specified by user is created */
    /* Error checking is also performed */
    if (setenv(name, value, 1) == -1) {
        perror("Error when creating shell variable ");
        return -1;
    }

    /* 0 is returned if setting of variable is successful */
    return 0;

}


/* int_exit() function starts here */
void int_exit() {

    printf("Goodbye!\n\n");

    /* Exits the eggshell */
    exit(0);
}


/* int_print() function starts here */
int int_print(char **args) {

    /* If the user entered a second argument, this part runs */
    if (args[1] != NULL) {

        /* Arguments entered are then printed to the console */
        for (int i = 1; args[i] != NULL; i++) {

            printf("%s ", args[i]);

        }

        /* If not, user is informed and -1 is returned */
    } else {
        perror("Nothing to print ");
        return -1;
    }

    /* A new line is added */
    putchar('\n');

    /* 0 returns if successful */
    return 0;

}


/* int_chdir() function starts here */
int int_chdir(char **args) {

    /* A character array of 100 chars is initialised */
    char len[100];

    /* If user enters more than 1 argument, this section runs */
    if (args[1] != NULL) {

        /* Directory is then changed and error checking is performed */
        if (chdir(args[1]) == -1) {
            perror("Error when changing directory ");
            return -1;
        }

        /* CWD shell variable is updated with the changes */
        if (setenv("CWD", getcwd(len, 100), 1) == -1) {
            perror("Error when modifying directory ");
            return -1;
        }

        /* If not, user is informed and program returns -1 */
    } else {
        perror("No directory specified ");
        return -1;
    }

    /* 0 is returned if successful */
    return 0;

}


/* int_all() function starts here */
int int_all() {

    /* Synopsis required to access the global environ variable */
    extern char **environ;

    /* Loops through all env variable and prints them */
    for (int i = 0; environ[i] != NULL; i++) {

        printf("%s \n", environ[i]);

    }

    /* Returns -125 back to main if successful */
    return -125;

}


/* int_source() function starts here */
int int_source(char **args) {

    /* A file pointer is created */
    FILE *fp;

    /* A string of 1000 chars is initialised */
    char str[1000];

    /* If the user enters a second argument, this section runs */
    if (args[1] != NULL) {

        /* If file exists and is opened successfully for reading, this section runs */
        if ((fp = fopen(args[1], "r")) != NULL) {

            /* Gets each line until EOF is reached */
            while (fgets(str, 1000, fp) != NULL) {

                /* Stored length of each line */
                int length = strlen(str);

                /* Replaces final new line char with null terminated string char */
                if (str[length - 1] == '\n') {

                    str[length - 1] = '\0';

                }

                /* The prompt and text from file are printed to stdout */
                fprintf(stdout, "%s", getenv("PROMPT"));
                fputs(str, stdout);

                /* New line is placed */
                putchar('\n');

                /* The line retrieved from file is split into args */
                run(args, str);

                /* The args are then processed for output */
                check_input(args);

            }

            /* file pointer is closed */
            fclose(fp);

            /* 0 is returned if successful */
            return 0;

            /* If not successfully opened, user is informed and
             * program returns -1 */
        } else {
            perror("File may not exist");
            return -1;
        }

        /* If just 1 arg is entered user is informed and -1 is returned */
    } else {
        perror("No filename specified");
        return -1;
    }

}


/* completion() function starts here */
void completion(const char *buf, linenoiseCompletions *lc) {

    /* Automatically replaces text similar to 'exit' with 'exit' when TAB is triggered*/
    if (buf[0] == 'e' || strcmp("ex", buf) == 0 || strcmp("exi", buf) == 0) {
        linenoiseAddCompletion(lc, "exit");
    }

    /* Automatically replaces text similar to 'print' with 'print' when TAB is triggered */
    if (buf[0] == 'p' || strcmp("pr", buf) == 0 ||
        strcmp("pri", buf) == 0 || strcmp("prin", buf) == 0) {
        linenoiseAddCompletion(lc, "print");
    }

    /* Automatically replaces text similar to 'chdir' with 'chdir' when TAB is triggered */
    if (buf[0] == 'c' || strcmp("ch", buf) == 0 ||
        strcmp("chd", buf) == 0 || strcmp("chdi", buf) == 0) {
        linenoiseAddCompletion(lc, "chdir");
    }

    /* Automatically replaces text similar to 'all' with 'all' when TAB is triggered */
    if (buf[0] == 'a' || strcmp("al", buf) == 0) {
        linenoiseAddCompletion(lc, "all");
    }

    /* Automatically replaces text similar to 'source' with 'source' when TAB is triggered */
    if (buf[0] == 's' || strcmp("so", buf) == 0 || strcmp("sou", buf) == 0
        || strcmp("sour", buf) == 0 || strcmp("sourc", buf) == 0) {
        linenoiseAddCompletion(lc, "source");
    }
}


/* check_input() function starts here */
int check_input(char **args) {

    /* Loops through all the arguments */
    for (int i = 1; args[i] != NULL; i++) {

        /* Pointer to individual arguments */
        char *show = args[i];

        /* If a dollar sign is identified as the first char in an arg */
        if (show[0] == '$') {

            /* Its corresponding shell var is retrieved */
            if ((show = getenv(&show[1])) == NULL) {
                perror("getenv() fail ");
                return -1;
            }

            /* If successfully retrieved, the argument is replaced with
             * the value received back */
            args[i] = show;

            /* If a \ is detected, this is simply removed from the argument */
        } else if (show[0] == '\\') {
            args[i] = &show[1];
        }

        /* A for loop which loops through all redirection operators */
        for (int j = 0; j < 4; j++) {

            /* If an entered argument matches a redirection operator
             * in the ops array, then the corresponding function pointer
             * value stored in that particular position is returned
             * which stores the address of the function to be computed*/
            if (strcmp(args[i], ops[j]) == 0) {

                return (*ops_address[j])(args, i);

            }

        }
    }

    /* Variable j is initialised to 0 */
    int j = 0;

    /* Section of code which checks for pipes */
    for (int i = 1; args[i] != NULL; i++) {

        if (strcmp(args[i], "|") == 0) {

            /* If found, the variable j holding the number of pipes is incremented */
            j++;
        }

    }

    /* If more than one pipe */
    if (j != 0) {

        /* Piping function is returned */
        return piping(args, j);

    }

    /* If = is detected in the first argument */
    if (strstr(args[0], "=") != NULL) {

        /* 2 char pointers are initialised */
        char *name;
        char *value;

        /* name stores the first part of the arg up till the = */
        name = strtok(args[0], "=");

        /* value stores the second part of the arg after the = */
        /* Error checking is performed to ensure the user entered a value */
        if ((value = strtok(NULL, "=")) == NULL) {
            perror("No value entered");
            return -1;
        }

        /* If value entered has a dollar sign as the first character */
        if (value[0] == '$') {

            /* this is replaced with the corresponding value it is storing */
            if ((value = getenv(&value[1])) == NULL) {
                perror("getenv() fail ");
                return -1;
            }

        }

        /* The function creating the shell variables is then returned */
        return create_shell_var(name, value);

        /* else if 'exit' is detected, this section runs */
    } else if (strcmp(args[0], "exit") == 0) {

        /* exit function is called */
        int_exit();

        /* else if 'print' is detected, this section runs */
    } else if (strcmp(args[0], "print") == 0) {

        /* print function is returned */
        return int_print(args);

        /* else if 'chdir' is detected, this section runs */
    } else if (strcmp(args[0], "chdir") == 0) {

        /* chdir function is returned */
        return int_chdir(args);

        /* else if 'all' is detected, this section runs */
    } else if (strcmp(args[0], "all") == 0) {

        /* all function is returned */
        return int_all();

        /* else if 'source' is detected, this section runs */
    } else if (strcmp(args[0], "source") == 0) {

        /* source function is returned */
        return int_source(args);

        /* else, the external commands function is returned */
    } else {

        return external(args);

    }


    /* -1 is returned on unsuccessful completion */
    return -1;

}


/* external() function starts here */
int external(char **args) {

    /* Variable to store the exit status */
    int status;

    /* The current process running is forked */
    pid_t pid = fork();

    /* If the child, then run this code */
    if (pid == 0) {

        /* execvp searches for a path which corresponds to the first
         * argument entered and tries to execute the command
         * If not, an error message is displayed and execution exits*/
        if (execvp(args[0], args) == -1) {
            perror("Error ");

            /* function which sets exitcode to errno is called */
            set_exit_when_fail();

            /* Execution is exited wit ha fail */
            exit(EXIT_FAILURE);
        }

        /* If pid has a value less than 0 forking failed */
    } else if (pid < 0) {

        perror("fork() failed");

        /* function which sets exitcode to errno is called */
        set_exit_when_fail();

        /* Execution is exited wit ha fail */
        exit(EXIT_FAILURE);
    }

    /* The parent process section */

    /* Parent wait for child to finish executing */
    waitpid(pid, &status, 0);

    /* On successful execution, 0 is returned */
    return 0;
}


/* forward_1_arrow() function starts here */
int forward_1_arrow(char **args, int i) {

    /* Local variables initialised at start */
    int a;
    char newline[1000] = "";
    int fd;
    int save_stdout, save_stderr;

    /* A file is opened in write mode with the appropriate flags set */
    /* If the file desc is not set accordingly, open() failed and -1 is returned */
    if ((fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        perror("open() fail");
        return -1;
    }

    /* All arguments entered up till the > operator are added to an array */
    for (a = 0; a < i; a++) {
        strcat(newline, args[a]);
        strcat(newline, " ");
    }

    /* Temporarily stores the STDOUT state to an int variable */
    if ((save_stdout = dup(STDOUT_FILENO)) == -1) {
        perror("dup() failed");
        close(fd);
        return -1;
    }

    /* Temporarily stores the STDERR state to an int variable */
    if ((save_stderr = dup(STDERR_FILENO)) == -1) {
        perror("dup() failed");
        close(fd);
        return -1;
    }

    /* The file descriptor opened is set to STDOUT */
    if ((dup2(fd, 1)) == -1) {
        perror("dup2() failed");
        close(fd);
        return -1;
    }

    /* It is also set to STDERR */
    if ((dup2(fd, 2)) == -1) {
        perror("dup2() failed");
        close(fd);
        return -1;
    }

    /* The file descriptor is then closed */
    close(fd);

    /* The newline string is then separated into args */
    run(args, newline);

    /* The args are processed */
    check_input(args);

    /* The STDOUT is then restored to the usual stdout */
    if ((dup2(save_stdout, STDOUT_FILENO)) == -1) {
        perror("dup2() failed");
        return -1;
    }

    /* The STDERR is then restored to the usual stderr */
    if ((dup2(save_stderr, STDERR_FILENO)) == -1) {
        perror("dup2() failed");
        return -1;
    }

    /* 0 is then returned if everything is successful */
    return 0;

}


/* forward_2_arrows() function starts here */
int forward_2_arrows(char **args, int i) {

    /* Local variables initialised at start */
    int a;
    int fd;
    char newline[1000] = "";
    int save_stdout, save_stderr;

    /* A file is opened in write and append mode with the appropriate flags set */
    /* If the file desc is not set accordingly, open() failed and -1 is returned */
    if ((fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1) {
        perror("open() fail");
        return -1;
    }

    /* All arguments entered up till the >> operator are added to an array */
    for (a = 0; a < i; a++) {
        strcat(newline, args[a]);
        strcat(newline, " ");
    }

    /* Temporarily stores the STDOUT state to an int variable */
    if ((save_stdout = dup(STDOUT_FILENO)) == -1) {
        perror("dup() failed");
        close(fd);
        return -1;
    }

    /* Temporarily stores the STDERR state to an int variable */
    if ((save_stderr = dup(STDERR_FILENO)) == -1) {
        perror("dup() failed");
        close(fd);
        return -1;
    }

    /* The file descriptor opened is set to STDOUT */
    if ((dup2(fd, 1)) == -1) {
        perror("dup2() failed");
        close(fd);
        return -1;
    }

    /* It is also set to STDERR */
    if ((dup2(fd, 2)) == -1) {
        perror("dup2() failed");
        close(fd);
        return -1;
    }

    /* The file descriptor is then closed */
    close(fd);

    /* The newline string is then separated into args */
    run(args, newline);

    /* The args are processed */
    check_input(args);

    /* The STDOUT is then restored to the usual stdout */
    if ((dup2(save_stdout, STDOUT_FILENO)) == -1) {
        perror("dup2() failed");
        return -1;
    }

    /* The STDERR is then restored to the usual stderr */
    if ((dup2(save_stderr, STDERR_FILENO)) == -1) {
        perror("dup2() failed");
        return -1;
    }

    /* 0 is then returned if everything is successful */
    return 0;

}


/* back_1_arrow() function starts here */
int back_1_arrow(char **args, int i) {

    /* Local variables initialised at start */
    int a;
    char newline[1000] = "";
    int save_stdin;
    int fd;

    /* A file is opened in read only mode with the appropriate flags set */
    /* If the file desc is not set accordingly, open() failed and -1 is returned */
    if ((fd = open(args[i + 1], O_RDONLY, 0444)) == -1) {
        perror("open() fail");
        return -1;
    }

    /* All arguments entered up till the < operator are added to an array */
    for (a = 0; a < i; a++) {
        strcat(newline, args[a]);
        strcat(newline, " ");
    }

    /* Temporarily stores the STDIN state to an int variable */
    if ((save_stdin = dup(STDIN_FILENO)) == -1) {
        perror("dup() failed");
        close(fd);
        return -1;
    }

    /* The file descriptor opened is set to STDIN */
    if ((dup2(fd, 0)) == -1) {
        perror("dup2() failed");
        close(fd);
        return -1;
    }

    /* Loops through all the remaining args and appends them to the newline string */
    for (a = i + 2; args[a] != NULL; a++) {
        strcat(newline, args[a]);
        strcat(newline, " ");
    }

    /* The newline string is then separated into args */
    run(args, newline);

    /* The args are processed */
    check_input(args);

    /* The STDIN is then restored to the usual stdin */
    if ((dup2(save_stdin, STDIN_FILENO)) == -1) {
        perror("dup2() failed");
        return -1;
    }

    /* The file descriptor is then closed */
    close(fd);

    /* 0 is then returned if everything is successful */
    return 0;
}

/*  */


/* back_3_arrows() function starts here */
int back_3_arrows(char **args, int i) {

    /* Local variables initialised at start */
    int a;
    int b = 0;
    char newline[1200] = "";
    char finalline[500] = "";
    char temp_array1[500] = "";
    char temp_array2[500] = "";

    char c;

    /* All arguments entered up till the <<<' operator are added to an array */
    for (a = 0; a < i; a++) {
        strcat(finalline, args[a]);
        strcat(finalline, " ");
    }

    /* Text is appended to the finalline string */
    strcat(finalline, "< temp.txt");

    /* Text is added to the newline string */
    strcat(newline, "print ");

    /* The arguments after the <<<' operator and on the same line as it
     * are added to the newline string */
    for(a = i+1 ; args[a] != NULL ; a++){
        strcat(newline, args[a]);
        strcat(newline, " ");
    }

    /* More text is added to the newline string */
    strcat(newline, "> temp.txt");

    /* The newline string is split into args */
    run(args, newline);

    /* These args are then processed */
    check_input(args);

    /* The character string newline is then emptied */
    memset(&newline[0], 0, sizeof(newline));

    /* Keeps reading the here string until user hits ' */
    while((c = getchar()) != '\''){

        /* Appends each entered character to another array */
        temp_array1[b++] = c;
    }
    /* Sets last element to '\0' */
    temp_array1[b] = '\0';

    /* Sets a and b to 0 */
    a = 0;
    b = 0;

    /* Loops until '\0' is reached */
    while(temp_array1[a] != '\0'){

        /* If '\n' is detected, certain contents are appended to newline string */
        if(temp_array1[a] == '\n'){
            strcat(newline, "print ");
            strcat(newline, temp_array2);
            strcat(newline, " >> temp.txt");

            /* These are then split into args */
            run(args, newline);

            /* The args are then evaluated */
            check_input(args);

            /* a increments and b is 0 */
            a++;
            b = 0;

            /* The character strings newline & temp_array2 are then emptied */
            memset(&temp_array2[0], 0, sizeof(temp_array2));
            memset(&newline[0], 0, sizeof(newline));

            /* continues */
            continue;
        }

        /* a char in temp_array1 is added to temp_array2 */
        temp_array2[b++] = temp_array1[a++];
    }

    /* More contents are added to newline string */
    strcat(newline, "print ");
    strcat(newline, temp_array2);
    strcat(newline, " >> temp.txt");

    /* These are then split into args */
    run(args, newline);

    /* And evaluated for output */
    check_input(args);

    printf("---\n");

    /* The finalline string is split into args */
    run(args, finalline);

    /* The input is evaluated */
    check_input(args);

    /* 0 is returned on success */
    return 0;

}


/* piping() function starts here */
int piping(char **args, int pipecount) {

    /* A character string is initialised */
    char str1[500] = "";

    /* char pointer is set to NULL at the start */
    char *token = NULL;

    /* tokenIndex set to 0 */
    int tokenIndex = 0;

    /* Commands array to store commands separated by "|" operator */
    char *commands[pipecount + 1];

    /* Pipes array to store file descriptors for each pipe */
    int pipes[pipecount][2];

    /* Int variables set to 0 at start */
    int save_stdin = 0;
    int save_stdout = 0;

    /* Loops through all entered args */
    for (int a = 0; args[a] != NULL; a++) {

        /* Appends args to the str1 char string */
        strcat(str1, args[a]);
        strcat(str1, " ");
    }

    /* Sets the 1st token to delimit "|" */
    token = strtok(str1, "|");

    /* Loops through all tokens */
    while (token != NULL) {

        /* Populates commands array with strings delimited */
        commands[tokenIndex] = token;

        /* Removes the first blank space */
        if (commands[tokenIndex][0] == ' ') {
            commands[tokenIndex] = &commands[tokenIndex][1];
        }

        /* Gets length of a command */
        int length = strlen(commands[tokenIndex]);

        /* Removes the last white space */
        if (commands[tokenIndex][length - 1] == ' ') {
            commands[tokenIndex][length - 1] = 0;
        }

        /* Constructs required to complete the looping process */
        token = strtok(NULL, "|");
        tokenIndex++;

    }

    /* Temporarily stores the STDIN state to an int variable */
    if ((save_stdin = dup(STDIN_FILENO)) == -1) {
        perror("dup() failed");
        return -1;
    }

    /* Temporarily stores the STDOUT state to an int variable */
    if ((save_stdout = dup(STDOUT_FILENO)) == -1) {
        perror("dup() failed");
        return -1;
    }

    /* Loops and creates all required pipes */
    for (int a = 0; a < pipecount + 1; ++a) {

        if ( a < pipecount) {

            /* Validation is performed if creating a particular pipe is unsuccessful */
            if ((pipe(pipes[a]) < 0)) {
                perror("pipe() failed");
                return -1;
            }
        }

        /* If not the first command, run this */
        if (a != 0) {

            /* Sets the file descriptor of the previous pipe to receive STDIN */
            if ((dup2(pipes[a-1][0], STDIN_FILENO)) < 0) {
                perror("Changing STDIN failed");
                return -1;
            }

        }

        /* If not the last command, run this */
        if (a < pipecount) {

            /* Sets the file descriptor of the current pipe to write to STDOUT */
            if ((dup2(pipes[a][1], STDOUT_FILENO)) < 0) {
                perror("Changing STDOUT failed");
                return -1;
            }

            /* If the last command is reached, this section runs */
        }else{

            /* The STDOUT is set once again to the normal stdout meaning
             * that the final result is printed out to the terminal*/
            if ((dup2(save_stdout, STDOUT_FILENO)) < 0) {
                perror("Changing STDOUT to terminal failed");
                return -1;
            }

        }

        /* If not the last command, run this */
        if(a < pipecount){

            /* Closes the current write pipe file descriptor */
            if(close(pipes[a][1]) < 0){
                perror("close() failed");
                return -1;
            }
        }

        /* If not the first command, run this */
        if(a > 0){
            /* Closes the previous read pipe file descriptor */
            if(close(pipes[a - 1][0]) < 0){
                perror("close() failed");
                return -1;
            }
        }

        /* The commands are then tokenised and split into args */
        run(args, commands[a]);

        /* The commands are then processed */
        check_input(args);
    }

    /* The STDIN is then restored to the usual stdin */
    if((dup2(save_stdin, STDIN_FILENO)) < 0){
        perror("dup2() failed");
        return -1;
    }

    /* The previously duped file descriptors are also closed */
    if((close(save_stdin) == -1) || (close(save_stdout) < 0)){
        perror("close() failed");
        return -1;
    }

    /* 0 is returned on successful implementation */
    return 0;
}


/* sigint_handler() function starts here */
void sigint_handler(int signal) {

    /* STDOUT is flushed */
    fflush(stdout);

    /* New line character is printed */
    putchar('\n');
}
