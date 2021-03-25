#ifndef SHOP_H
#define SHOP_H
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

int handle_shop(int pipefd_city[2],string city_adr,string shop_name);

#endif