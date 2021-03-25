#include "shophandling.h"
#include "date_analizing.h"
int handle_shop(int pipefd_city[2],string city_adr,string shop_name)
{
    char max_min[256];
    char id[256];
    char start_date[256];
    char end_date[256];
    char shop_in_province[256];
    char shop_in_city[256];
    int final_result;

    for(int i =0;i<6;i++)
    {
        char data_to_receive[256] = "";
        int n = read(pipefd_city[0],data_to_receive,256);
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
                shop_in_province[j] = data_to_receive[j];
        }
        if(i==5)
        { 
            for(int j=0;j<256;j++)
                shop_in_city[j] = data_to_receive[j];
        }
    }
    string shop_adr = city_adr + "/" + shop_name ;

    final_result = process_data_in_csv_file(max_min,id,start_date,end_date,
                                            shop_in_province,shop_in_city,shop_adr);
    return final_result;
}
