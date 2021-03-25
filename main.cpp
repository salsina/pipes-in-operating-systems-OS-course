#include <iostream>
#include <string>
#include <vector>
#include "reading_file_cmds.h"
#include "openinitdir.h"

using namespace std;

int main(int argc,char* argv[])
{
    if(argc > 3)
    {
        cout<<"Wrong Input\n";
        exit(1);
    }
    string command_adr = argv[1];
    string shop_info_files = argv[2];
    vector<vector<string>> commands;
    commands = read_from_commandtext(command_adr);
    for(int i=0;i<commands.size();i++)
    {
        int result = open_init_directory(shop_info_files,commands[i]);
        cout<<result<<endl;
    }
    return 0;
}