#ifndef RDFILE_H
#define RDFILE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include<dirent.h>
using namespace std;

vector<vector<string>> read_from_commandtext(string cmd_adr);
void check_if_dir_exists(DIR* dr);

#endif