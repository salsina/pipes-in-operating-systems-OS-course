#ifndef CITY_H
#define CITY_H
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

int calc_max_result(vector<int> results);
int calc_min_result(vector<int> results);
int handle_cities(int pipefd_province[2],string province_adr,string city_name);


#endif