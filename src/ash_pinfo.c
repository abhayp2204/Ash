#include "../include/shell.h"
#include "../include/variables.h"
#include "../include/functions.h"

char* extract_pid_string();
pid_t extract_pid_int();
char* get_process_stat(char pid_string[]);
int valid_pid();
void process_pid(pid_t pid);
void process_status(char process_stat[]);
void process_memory(char process_stat[]);
void process_path(pid_t pid);

void ash_pinfo()
{
    pid_t pid = extract_pid_int();
    char* pid_string = malloc(1024);
    char* process_stat = malloc(1024);
    char* process_exe = malloc(1024);

    strcpy(pid_string, extract_pid_string());
    strcpy(process_stat, get_process_stat(pid_string));
    strcpy(process_exe, get_process_stat(pid_string));

    if(!valid_pid()) return;

    // Display
    process_pid(pid);
    process_status(process_stat);
    process_memory(process_stat);
    process_path(pid);
}

char* extract_pid_string()
{
    pid_t pid;
    char* temp_pid = malloc(20);
    char* copy = malloc(strlen(parsed_input));
    char* temp = malloc(20);

    strcpy(copy, parsed_input);
    strtok(copy, " ");
    temp_pid = strtok(NULL, " ");

    // pinfo without parameter
    if(!temp_pid)
    {
        snprintf(temp, 20, "%d", getpid());
        return temp;
    }

    return temp_pid;
}

pid_t extract_pid_int()
{
    pid_t pid;
    char *temp_pid = malloc(20);
    strcpy(temp_pid, extract_pid_string());

    // If only "pinfo" is entered without a parameter
    if(!strlen(temp_pid))
        return getpid();    

    sscanf(temp_pid, "%d", &pid);
    return pid;
}

char* get_process_stat(char pid_string[])
{
    char *process_stat = malloc(1024);

    strcpy(process_stat, "/proc/");
    strcat(process_stat, pid_string);
    strcat(process_stat, "/stat");

    return process_stat;
}

char* get_process_exe(char pid_string[])
{
    char *process_exe = malloc(1024);

    strcpy(process_exe, "/proc/");
    strcat(process_exe, pid_string);
    strcat(process_exe, "/exe");

    return process_exe;
}

int valid_pid(char process_stat[])
{
    struct stat stats;

    if(stat(process_stat, &stats) == -1 && errno == ENOENT)
    {
        printf("There is no process with pid %d\n", extract_pid_int());
        return 0;
    }
    return 1;
}

void process_pid(pid_t pid)
{
    printf("pid -- %d\n", pid);
}

void process_status(char process_stat[])
{
    // Read temp 
    FILE *fd = fopen(process_stat, "r");
    if(fd == NULL)
    {
        printf("error\n");
        return;
    }

    char ch;
    char plus;
    int spaces = 0;

    while (1)
    {
        // Read character
        ch = fgetc(fd);

        spaces += is_space(ch);

        // Get the status character and return
        if(spaces == 2)
        {
            ch = fgetc(fd);
            plus = fgetc(fd);
            printf("Process Status -- %c%c\n", ch, plus);
            break;
        }

        if(spaces > 2)
        {
            printf("ash_pinfo: There was an error getting process status\n");
            break;
        }
 
        // printf("%c", ch);
    }

    fclose(fd);
}

void process_memory(char process_stat[])
{
    FILE *fd = fopen(process_stat, "r");
    fseek(fd, 0, SEEK_SET);
    char *virtual_memory = malloc(1024);
    char ch;
    int spaces = 0;

    while(1)
    {
        ch = fgetc(fd);
        spaces += is_space(ch);

        if(spaces == 22)
        {
            int i = 0;
            ch = fgetc(fd);
            while(!is_space(ch))
            {
                virtual_memory[i++] = ch;
                ch = fgetc(fd);
            }
            virtual_memory[i] = '\0';
            int vm_b;
            sscanf(virtual_memory, "%d", &vm_b);

            fclose(fd);

            float vm_kb = vm_b / 1024.0;
            float vm_mb = vm_kb / 1024.0;

            // Print in bytes
            if((int)vm_kb == 0)
            {
                printf("Memory -- %d bytes\n", vm_b);
                return;
            }
            // Print in KB
            if((int)vm_mb == 0)
            {
                printf("Memory -- %.2lf KB\n", vm_kb);
                return;
            }
            // Print in MB
            printf("Memory -- %.2lf MB\n", vm_mb);
            return;
        }
    }
   
    // printf("memory -- %lld\n", virtual_memory_size);
}

void process_path(pid_t pid)
{
    char process_path[1024];
    char *path = (char*)malloc(1024*sizeof(char));
    sprintf(path, "/proc/%d/exe", pid);

    ssize_t ret = readlink(path, process_path, 1024);
    if (ret > 0)
    {
        process_path[ret] = 0;
    }
    else
        perror("readlink");

    if(at_home(process_path))
    {
        printf("Pathhhhh -- %s\n", process_path);
        return;
    }

    if(!subdirectory_of_home(process_path))
    {
        printf("Path -- %s\n", process_path);
        return;
    }

    char *dir = malloc(strlen(process_path) + 2);
    dir[0] = '~';
    dir[1] = '/';
    int j = 2;

    for(int i = strlen(home) + 1 ; i < strlen(process_path) ; i++)
    {
        dir[j++] = process_path[i];
    }
    dir[j] = '\0';  
    printf("Path -- %s\n", dir);
    free(dir);
}