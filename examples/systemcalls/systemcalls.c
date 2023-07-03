#include "systemcalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    return system(cmd) == 0;
}

bool is_absolute_path(const char* path)
{
    bool status = (path != NULL && path[0] == '/');
    return status;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();
    if(pid == -1){
        return false;
    }
    else if(pid == 0){
        if (count == 2 && !is_absolute_path(command[0]))
        {
            perror("Command should be specified with an absolute path.\n");
            return false;
        }
        if (count == 3 && !is_absolute_path(command[0]) && !is_absolute_path(command[2]))
        {
            perror("Command should be specified with an absolute path.\n");
            return false;
        }
        execv(command[0], command);
        //execv only returns if an error occurred
        return false;
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        if (count == 2 && !is_absolute_path(command[0]))
        {
            perror("Command should be specified with an absolute path.\n");
            return false;
        }        //check the exit status of the child process
        if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
            return true;
        }
        else{
            return false;
        }
    }
    va_end(args);
}


/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (fd < 0) { perror("open"); abort(); }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork"); abort();
        return false;
    }
    else if(pid == 0){
        if (dup2(fd, 1) < 0) { perror("dup2"); abort(); }
        execv(command[0], command);
        perror("fork"); abort();
        //execv only returns if an error occurred
        return false;
    }
    else{
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        //check the exit status of the child process
        if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
            return true;
        }
        else{
            return false;
        }
    }
    va_end(args);
    return true;
}
