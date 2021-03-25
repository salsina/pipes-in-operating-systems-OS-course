#include "cityhandling.h"
#include "shophandling.h"
#include "reading_file_cmds.h"

int calc_max_result(vector<int> results)
{
    int max = results[0];
    for(int i=1;i<results.size();i++)
        if(results[i] > max)
            max = results[i];
    return max;
}

int calc_min_result(vector<int> results)
{
    int min = results[0];
    for(int i=1;i<results.size();i++)
        if(results[i] < min)
            min = results[i];
    return min;
}

int handle_cities(int pipefd_province[2],string province_adr,string city_name)
{
    char max_min[256];
    char id[256];
    char start_date[256];
    char end_date[256];
    char province_name_to_send[256];
    char name_to_send[256];
    for(int i=0;i<city_name.size();i++)
        name_to_send[i] = city_name[i];

    for(int i =0;i<5;i++)
    {
        char data_to_receive[256] = "";
        int n = read(pipefd_province[0],data_to_receive,256);
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
        if(i==4)
        { 
            for(int j=0;j<256;j++)
                province_name_to_send[j] = data_to_receive[j];
        }
    }
    string cur_adr = province_adr + "/" + city_name ;

    struct dirent *de; 
    DIR* dr = opendir(cur_adr.c_str()); 
    check_if_dir_exists(dr);

    vector<int> shop_fds;

    for(int i=0;i<shop_fds.size();i++)
        cout<<shop_fds[i]<<"  ";

    vector<int> shop_answers;
    while ((de = readdir(dr)) != NULL)
    {
        string shop_name = de->d_name;
        if(shop_name[0] != '.' )
        {
            int pipefd_city[2];
            pipe(pipefd_city);
            int pid = fork();
            string pipe_name;
            if(pid != 0)
                pipe_name = to_string(pid);
            else    
                pipe_name = to_string(getpid());
            mkfifo(pipe_name.c_str(),0666);
            int fd;
            int res;
            if(pid == 0)
            {
                res = handle_shop(pipefd_city,cur_adr,shop_name);
                fd = open(pipe_name.c_str(),O_WRONLY);
                write(fd,to_string(res).c_str(),256);
                close(fd);
                exit(0);
                break;
            }
            else if (pid>0)
            {
                write(pipefd_city[1],max_min,256);
                write(pipefd_city[1],id,256);
                write(pipefd_city[1],start_date,256);
                write(pipefd_city[1],end_date,256);
                write(pipefd_city[1],province_name_to_send,256);
                write(pipefd_city[1],name_to_send,256);
                fd = open(pipe_name.c_str(),O_RDONLY);
                char ans[256];
                read(fd,ans,256);
                shop_answers.push_back(atoi(ans));
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
        return calc_max_result(shop_answers);
    }
    return calc_min_result(shop_answers);
}
