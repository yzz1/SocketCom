#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("10.70.9.60");  //具体的IP地址
    serv_addr.sin_port = htons(12345);  //端口
    int result_connect = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  
    if(result_connect == 0 )
      printf("client connect server success!\n");
    else
      printf("client connect server failed, errorcode = %d\n",result_connect);
   
    //读取服务器传回的数据
    char ChaoSu_str[2] ="1";
    char FrontCrash_str[2] = "2";
    bool reverse = true;
    
    while(1)
    {
    if(reverse == true)
      write(sock, ChaoSu_str, sizeof(ChaoSu_str));
    else
      write(sock, FrontCrash_str, sizeof(FrontCrash_str));
    reverse = !reverse;   
    sleep(1);   
    }
    //关闭套接字
    close(sock);

    return 0;
}
