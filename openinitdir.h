#ifndef INIT_H
#define INIT_H
#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iterator>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int open_init_directory(string shop_info_files_path,vector<string> cur_command);

#endif