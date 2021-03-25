#ifndef PROVINCE_H
#define PROVINCE_H
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

int handle_provinces(int pipefd_init[2],string shop_info_files_path,string province_name);

#endif