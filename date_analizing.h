#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 
#include<dirent.h>
using namespace std;

vector<int> make_date_tokenized(string date);
bool is_in_dates(char* starting_date,char* ending_date,string date);
int process_data_in_csv_file(char max_min[256],char id[256],char start_date[256],char end_date[256],
                            char shop_in_province[256],char shop_in_city[256],string shop_adr);

#endif