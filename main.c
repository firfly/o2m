//
//  main.c
//  o2m
//
//  Created by dbtony on 14-10-8.
//  Copyright (c) 2014年 acoug. All rights reserved.
//

#include <stdio.h>
#include "mysql.h"
#include <string.h>

int main(int argc, const char * argv[]) {
    MYSQL * con; //= mysql_init(MYSQL*) 0);
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    char tmp[400];
    
    //database configuration
    char dbuser[30]="dbtony";
    char dbpasswd[30]="dbtony";
    char dbip[30]="10.1.200.142";
    char dbname[50]="employees";
    char tablename[50]="dept_manager";
    char *query=NULL;
    
    
    int x,y,rt;  // rt:return value
    unsigned int t;
    
    int count = 0;
    
    printf("input x,y\n");
    scanf("%d,%d",&x,&y);
    fflush(stdin);
    printf("input over\n");
    con = mysql_init((MYSQL*) 0);
    
    if (con !=NULL && mysql_real_connect(con,dbip,dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Sock 连接类型*/, 0/*运行成ODBC数据库标志*/))
        
    {
        if (!mysql_select_db(con, dbname))
        {
            printf("select Successfully the database!\n");
            
            con ->reconnect = 1;
            
            query ="set names \'GBK\'";
            //mysql_query(con,"set names \'BGK\'");
            
            rt = mysql_real_query(con, query, strlen(query));
            if (rt)
            {
                printf("Error making query: %s !!!\n",mysql_error(con));
            }
            else
            {
                printf("query %s succeed!\n",query);
            }
            
        }
    }
    
    else
    {
//        MessageBoxA(NULL,"Unable to connect the database,check your configuration!","",NULL);
        fprintf(stderr, "Unable to connect the database,check your configuration!\n");
        fprintf(stderr, "Probably cause: %s\n",mysql_error(con));
    }
    
    sprintf(tmp, "select * from %s",tablename);
    
    rt = mysql_real_query(con, tmp, strlen(tmp));
    if (rt)
    {
        printf("Error making query: %s !!!",mysql_error(con));
    }
    else
    {
        printf("%s executed!!!\n",tmp);
    }

    res = mysql_store_result(con); //将结果保存在res结构体中
    
    while ((row = mysql_fetch_row(res))) {
        /**
         ** MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result); 
         * 检索行
         */
        
        for (t=0; t<mysql_num_fields(res);t++) {
            printf("%s   ",row[t]);
        }
        printf("..............\n");
        count ++;
    }
    printf("number of rows %d\n",count);
    printf("mysql_free_result...\n");
    mysql_free_result(res);
    
    mysql_close(con);
    return 0;
    
    
    
    
    
    
    
    
    
        }







