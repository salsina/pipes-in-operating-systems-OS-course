#include "openinitdir.h"
#include "provhandling.h"
#include "reading_file_cmds.h"
#include "cityhandling.h"

int open_init_directory(string shop_info_files_path,vector<string> cur_command)
{
    struct dirent *de; 
    DIR* dr = opendir(shop_info_files_path.c_str()); 
    check_if_dir_exists(dr);
    vector<int> province_answers;
    while ((de = readdir(dr)) != NULL)
    {
        string province_name = de->d_name;
        if(province_name[0] != '.' )
        {
            int pipefd_init[2];
            pipe(pipefd_init);
            int pid = fork();
            string pipe_name;
            if(pid != 0)
                pipe_name = to_string(pid);
            else    
                pipe_name = to_string(getpid());

            mkfifo(pipe_name.c_str(),0666);
            int fd;
            if(pid == 0)
            {
                int res = handle_provinces(pipefd_init,shop_info_files_path,province_name);
                fd = open(pipe_name.c_str(),O_WRONLY);
                write(fd,to_string(res).c_str(),256);
                close(fd);
                exit(0);
                break;
            }
            else if (pid>0)
            {
                for(int i =0;i<cur_command.size();i++)
                {
                    char data_to_send[256] = "";
                    for(int j=0;j<cur_command[i].size();j++)
                    {
                        data_to_send[j] = cur_command[i][j];
                    }
                    int n = write(pipefd_init[1],data_to_send,256);
                    if(n<0) {cout<<"failed to write\n"; exit(1);}
                }
                fd = open(pipe_name.c_str(),O_RDONLY);
                char ans[256];
                read(fd,ans,256);
                province_answers.push_back(atoi(ans));
                wait(NULL);
            }
            else{
                cout<<"Error forking\n";
                exit(1);
            }
        }
    }
    closedir(dr);
    string max_min = cur_command[0];
    if (max_min[1] == 'A')
    {
        return calc_max_result(province_answers);
    }
    return calc_min_result(province_answers);

}
