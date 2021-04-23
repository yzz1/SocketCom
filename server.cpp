#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;


int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("10.70.9.60");  //具体的IP地址
    serv_addr.sin_port = htons(12345);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //向客户端发送数据
    char str[] = "http://c.biancheng.net/socket/";
    write(clnt_sock, str, sizeof(str));

   char buffer[40];
    string ChaoSu_str ="1";
    string FrontCrash_str = "2";

    printf("line:%d ",__LINE__); 
    while(1)
    {
    memset(buffer,0,40);
    
    if( read(clnt_sock, buffer, sizeof(buffer)-1) <=0)
     {	
         close(clnt_sock);
         clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); 
         continue;
      }
    string buf_str = buffer;
   if(buf_str.compare(ChaoSu_str) ==0 )
        printf("Chao Su yujing\n-->HMI; -->tts\n"); 
   else if(buf_str.compare(FrontCrash_str) ==0 )
        printf("FrontCrash\n--HMI;--tts\n");
   else
       { printf("cound not compare any Message form server: %s\n", buffer); continue;}
     
    printf("line:%d ",__LINE__); 
    }

    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
