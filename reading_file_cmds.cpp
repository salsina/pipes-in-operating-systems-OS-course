#include"reading_file_cmds.h"
using namespace std;
vector<vector<string>> read_from_commandtext(string cmd_adr)
{
    fstream file; 
    string word,line; 
    vector<vector<string>> commands;
    file.open(cmd_adr.c_str()); 
  
    while(getline(file,line,'\n'))
    {
        vector <string> tokens;
        stringstream check1(line); 
        string intermediate; 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        } 
        commands.push_back(tokens);      
    }
    file.close();
    return commands;
}

void check_if_dir_exists(DIR* dr)
{
    if (dr == NULL)   
    { 
        cout<<"Could not open current directory\n"; 
        exit(1);
    } 
}

