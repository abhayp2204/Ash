#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// Flags
int flag_l = 0;
int flag_a = 0;
int flag_invalid = 0;

// Functions
void find_flags();
void reset_flags();
void ls(char* dir);
void display_total(char* dir);
void display_permissions(struct stat stats, struct dirent* d, char* dir);
void display_number_of_links(struct stat stats, struct dirent* d);
void display_user_name(struct stat stats, struct dirent* d);
void display_group_name(struct stat stats, struct dirent* d);
void display_size(struct stat stats, struct dirent* d);
void display_date_modified(struct stat stats, struct dirent* d);
char* get_month(char month[]);

void ash_ls(char path[])
{
    // printf("input = %s\n", parsed_input);
    find_flags();

    if(chdir(path) == -1)
    {
        cprint("ash_ls", "Could not read directory");
        return;
    }
    
    ls(".");
    chdir(cwd);
    reset_flags();
}

void find_flags()
{
    char* copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);
    char delimiter[] = " ";
    char* token = strtok(copy, delimiter);
    token = strtok(NULL, delimiter);

    while(token)
    {
        if(token[0] != '-')
        {
            token = strtok(NULL, delimiter);
            continue;
        }

        for(int i = 1 ; i < strlen(token) ; i++)
        {
            if(token[i] == 'l')
                flag_l = 1;
            else if(token[i] == 'a')
                flag_a = 1;
            else
                flag_invalid = 1;
        }

        if(flag_invalid)
        {
            cprint("ash_ls", "Invalid flags were entered, only valid flags were considered");
            return;
        }

        token = strtok(NULL, delimiter);
    }

    int dir_count = 0;
}

void reset_flags()
{
    flag_l = 0;
    flag_a = 0;
    flag_invalid = 0;
}

void ls(char* dir)
{
    struct dirent* d;
    DIR *dh = opendir(dir);

    if(!dh)
    {
        cprint("ash_ls", "Could not read directory");
        return;
    }
    closedir(dh);

    struct stat stats;

    if(flag_l)
        display_total(dir);

    dh = opendir(dir);
    while(d = readdir(dh))
    {
        struct stat stats;

        // Skip hidden files unless -a is specified
        if(!flag_a && d->d_name[0] == '.')
            continue;

        if(flag_l)
        {
            // printf("path = %s\t", dir);
            display_permissions(stats, d, dir);
            display_number_of_links(stats, d);
            // display_user_name(stats, d);
            display_group_name(stats, d);
            display_group_name(stats, d);
            display_size(stats, d);
            display_date_modified(stats, d);
        }
        printf("%s  ", d->d_name);
        if(flag_l)
            printf("\n");
    }
    closedir(dh);

    if(!flag_l)
        printf("\n");
}

void display_total(char* dir)
{
    DIR* dh = opendir(dir);
    struct dirent* d;
    struct stat stats;

    int total = 0;
    
    if(!dir)
        return;

    while(d = readdir(dh))
    {
        // Ignore hidden files
        if(d->d_name[0] == '.')
            continue;
        
        // Create the path to stat
        char info_path[PATH_MAX + 1];
        strcpy(info_path, dir);
        
        if(dir[strlen(dir) - 1] != '/')
           strcat(info_path, "/");
        strcat(info_path, d->d_name);

        // Increment total
        stat(info_path, &stats);
        total += stats.st_blocks;
    }
    printf("total %d\n", total/2);
}

void display_permissions(struct stat stats, struct dirent* d, char* dir)
{
    stat(d->d_name, &stats);

    // File / Directory
    printf("%c", (opendir(d->d_name))? 'd':'-');

    // User
    printf("%c", (stats.st_mode & S_IRUSR)? 'r':'-');
    printf("%c", (stats.st_mode & S_IWUSR)? 'w':'-');
    printf("%c", (stats.st_mode & S_IXUSR)? 'x':'-');

    // Group
    printf("%c", (stats.st_mode & S_IRGRP)? 'r':'-');
    printf("%c", (stats.st_mode & S_IWGRP)? 'w':'-');
    printf("%c", (stats.st_mode & S_IXGRP)? 'x':'-');

    // Other
    printf("%c", (stats.st_mode & S_IROTH)? 'r':'-');
    printf("%c", (stats.st_mode & S_IWOTH)? 'w':'-');
    printf("%c", (stats.st_mode & S_IXOTH)? 'x':'-');

    printf("   ");
}

void display_number_of_links(struct stat stats, struct dirent* d)
{
    lstat(d->d_name, &stats);
    printf("%ld   ", stats.st_nlink);
}

void display_user_name(struct stat stats, struct dirent* d)
{
    // struct passwd *user = getpwuid(stats.st_uid);
    // printf("%s   ", user->pw_name);

    printf("%s\t", username);
}

void display_group_name(struct stat stats, struct dirent* d)
{
    // struct group *group = getgrgid(stats.st_gid);
    // printf("%s   ", group->gr_name);

    printf("%s\t", username);
}

void display_size(struct stat stats, struct dirent* d)
{
    stat(d->d_name, &stats);
    printf("%ld\t", stats.st_size);
}

void display_date_modified(struct stat stats, struct dirent* d)
{
    stat(d->d_name, &stats);

    char month_number[3];
    strftime(month_number, sizeof(month_number), "%m", localtime(&stats.st_mtime));

    char month[3];
    strcpy(month, get_month(month_number));
    // printf("%s ", month);

    char day[2];
    // strftime(day, sizeof(day), "%D", localtime(&stats.st_mtime));

    char time[10];
    // strftime(time, sizeof(time), "%H:%M", localtime(&stats.st_mtime));
    // strftime(time, sizeof(time), "%s", ctime(&stats.st_mtime));
    int n = strlen(ctime(&stats.st_mtime));
    printf("%s\t", substring(ctime(&stats.st_mtime), 4, n-1-4-3));
    // printf("%s   ", time);
}

char* get_month(char month_number[])
{
    if(!strcmp(month_number, "01"))
        return "Jan";
    if(!strcmp(month_number, "02"))
        return "Feb";
    if(!strcmp(month_number, "03"))
        return "Mar";
    if(!strcmp(month_number, "04"))
        return "Apr";
    if(!strcmp(month_number, "05"))
        return "May";
    if(!strcmp(month_number, "06"))
        return "Jun";
    if(!strcmp(month_number, "07"))
        return "Jul";
    if(!strcmp(month_number, "08"))
        return "Aug";
    if(!strcmp(month_number, "09"))
        return "Sep";
    if(!strcmp(month_number, "10"))
        return "Oct";
    if(!strcmp(month_number, "11"))
        return "Nov";
    if(!strcmp(month_number, "12"))
        return "Dec";
}