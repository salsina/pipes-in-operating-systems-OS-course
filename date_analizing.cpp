#include "date_analizing.h"
using namespace std;
vector<int> make_date_tokenized(string date)
{
    vector<int> tokenized_date;
    stringstream check1(date); 
    string intermediate; 
    while(getline(check1, intermediate, '/')) 
    { 
        tokenized_date.push_back(stoi(intermediate)); 
    } 
    return tokenized_date;
}

bool is_in_dates(char* starting_date,char* ending_date,string date)
{

    vector<int> tokenized_starting_date;
    vector<int> tokenized_ending_date;
    vector<int> tokenized_date ;

    tokenized_starting_date = make_date_tokenized(starting_date);
    tokenized_ending_date = make_date_tokenized(ending_date);
    tokenized_date = make_date_tokenized(date);

    if(tokenized_date[0] < tokenized_starting_date[0])
        return false;
    if(tokenized_date[0] == tokenized_starting_date[0])
    {
        if(tokenized_date[1] < tokenized_starting_date[1])
            return false;
        if(tokenized_date[1] == tokenized_starting_date[1])
        {
            if(tokenized_date[2] < tokenized_starting_date[2])
                return false;
        }
    }

    if(tokenized_date[0] > tokenized_ending_date[0])
        return false;
    if(tokenized_date[0] == tokenized_ending_date[0])
    {
        if(tokenized_date[1] > tokenized_ending_date[1])
            return false;
        if(tokenized_date[1] == tokenized_ending_date[1])
        {
            if(tokenized_date[2] > tokenized_ending_date[2])
                return false;
        }
    }

    return true;
}

int process_data_in_csv_file(char max_min[256],char id[256],char start_date[256],char end_date[256],
                            char shop_in_province[256],char shop_in_city[256],string shop_adr)
{
    string line;
    ifstream file;
    file.open(shop_adr);
    getline(file,line,'\n');
    vector <vector<string>> products;
    int max_result=-1;
    int min_result = -1;
    while(getline(file,line,'\n'))
    {
        vector <string> tokens;
        stringstream check1(line); 
        string intermediate; 
        while(getline(check1, intermediate, ',')) 
        { 
            tokens.push_back(intermediate); 
        } 
        products.push_back(tokens);      
    }

    for(int i=0;i<products.size();i++)
    {
        if(products[i][1] == id)
        {
            if(is_in_dates(start_date,end_date,products[i][0]))  
            {
                if(max_min[1] == 'A')
                {
                    if(stoi(products[i][2]) > max_result)
                        max_result = stoi(products[i][2]);
                }
                else if(max_min[1] == 'I')
                {
                    if (min_result == -1)
                        min_result = stoi(products[i][2]);
                    else if(stoi(products[i][2]) < min_result)
                        min_result = stoi(products[i][2]);
                }
            }
        }
    }

    if(min_result == -1 && max_result == -1)
        return -1;
    if(min_result == -1)
    {
        return max_result;
    }
    return min_result;

} 

