#include "../include/functions.h"
#include "../include/variables.h"

int flag_l = 0;
int flag_a = 0;
int flag_invalid = 0;

void find_flags();
void reset_flags();
void ls(const char* dir);
void display_permissions(struct stat stats, struct dirent* d);
void display_number_of_links(struct stat stats, struct dirent* d);
void display_user_name(struct stat stats, struct dirent* d);
void display_group_name(struct stat stats, struct dirent* d);

void ash_ls()
{
    // printf("input = %s\n", parsed_input);
    find_flags();
    ls(".");

    reset_flags();
}

void find_flags()
{
    char delimiter[] = " ";
    char* token = strtok(parsed_input, delimiter);
    token = strtok(NULL, delimiter);

    while(token)
    {
        if(token[0] != '-')
        {
            // printf("token = %s\n", token);
            // chdir(token);

            printf("ash_ls: Please use '-' for flags\n");
            break;
        }

        // printf("token = %s\n", token);
        // printf("len = %ld\n", strlen(token));
        // printf("token[0] = %c\n", token[0]);

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
            printf("ash_ls: Invalid flags were entered\n");
            reset_flags();
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

void ls(const char* dir)
{
    struct dirent* d;
    DIR *dh = opendir(dir);

    if(!dh)
    {
        printf("ash_ls: Unable to read directory\n");
        return;
    }

    struct stat stats;
    while(d = readdir(dh))
    {
        // Skip hidden files unless -a is specified
        if(!flag_a && d->d_name[0] == '.')
            continue;

        if(flag_l)
        {
            display_permissions(stats, d);
            display_number_of_links(stats, d);

            // Root???
            display_user_name(stats, d);
            display_group_name(stats, d);

            
        }
        printf("%s  \n", d->d_name);
    }
    printf("\n");
}

void display_permissions(struct stat stats, struct dirent* d)
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
    struct passwd *user = getpwuid(stats.st_uid);
    printf("%s   ", user->pw_name);
}

void display_group_name(struct stat stats, struct dirent* d)
{
    struct passwd *user = getpwuid(stats.st_uid);
    printf("%s   ", group->gr_name);
}