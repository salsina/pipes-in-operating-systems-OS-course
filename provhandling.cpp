#include "provhandling.h"
#include "cityhandling.h"
#include "reading_file_cmds.h"

int handle_provinces(int pipefd_init[2],string shop_info_files_path,string province_name)
{
    char max_min[256];
    char id[256];
    char start_date[256];
    char end_date[256];
    char name_to_send[256];
    for(int i=0;i<province_name.size();i++)
        name_to_send[i] = province_name[i];

    for(int i =0;i<4;i++)
    {
        char data_to_receive[256] = "";
        int n = read(pipefd_init[0],data_to_receive,256);
        if(n<0) {cout<<"failed to read\n"; exit(1);}
        if(i==0)
        {
            for(int j=0;j<256;j++)
                max_min[j] = data_to_receive[j];
        }
        if(i==1)
        {       
            for(int j=0;j<256;j++)
                id[j] = data_to_receive[j];
        }
        if(i==2)
        {    
            for(int j=0;j<256;j++)
                start_date[j] = data_to_receive[j];
        }
        if(i==3)
        { 
            for(int j=0;j<256;j++)
                end_date[j] = data_to_receive[j];
        }
    }
    string cur_adr = shop_info_files_path + "/" + province_name ;

    struct dirent *de; 
    DIR* dr = opendir(cur_adr.c_str()); 
    check_if_dir_exists(dr);
    vector<int> city_answers;
    while ((de = readdir(dr)) != NULL)
    {
        string city_name = de->d_name;
        if(city_name[0] != '.' )
        {
            int pipefd_province[2];
            pipe(pipefd_province);
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
                int res = handle_cities(pipefd_province,cur_adr,city_name);
                fd = open(pipe_name.c_str(),O_WRONLY);
                write(fd,to_string(res).c_str(),256);
                close(fd);
                exit(0);
                break;
            }
            else if (pid>0)
            {
                write(pipefd_province[1],max_min,256);
                write(pipefd_province[1],id,256);
                write(pipefd_province[1],start_date,256);
                write(pipefd_province[1],end_date,256);
                write(pipefd_province[1],name_to_send,256);
                fd = open(pipe_name.c_str(),O_RDONLY);
                char ans[256];
                read(fd,ans,256);
                city_answers.push_back(atoi(ans));
                wait(NULL);
            }
            else{
                cout<<"Error forking\n";
                exit(1);
            }
        }
    }
    closedir(dr);
    if (max_min[1] == 'A')
    {
        return calc_max_result(city_answers);
    }
    return calc_min_result(city_answers);

}
