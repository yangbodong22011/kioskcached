#include "anet.h"
#include "define.h"
#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int items = argc > 1 ? atoi(argv[1]) : 10000;
    int keylen = argc > 2 ? atoi(argv[2]) : 24;
    int valuelen = argc > 3 ? atoi(argv[3]) : 1000;

    /*char err[ANET_ERR_LEN];
    int conn_fd = anetTcpConnect(err, "127.0.0.1", DEFAULT_LISTEN_PORT);
    if (conn_fd == ANET_ERR) {
        printf("connect error: %s\n", err);
        return -1;
    }*/

    package_t *package = alloc_packet(1024 + 1);
    package->head.type = KIO_SET;

    char key[50] = {0};
    char value[1024] = {0};
    char buff[1024] = {0};
    
    for(int i = 0;i < items;++i) {
        snprintf(key,sizeof(key),"%0*d",keylen,i);
        snprintf(value,sizeof(value),"%s","abcdefghijklmnopqrstuvwxyz");
        snprintf(buff,sizeof(buff),"%s%s",key,value);
    
        printf("%s\n",key);
        printf("%s\n",value);

        /*memcpy(package->data,buff,strlen(buff)+1);
        int package_len = sizeof(package_head_t) + package->head.length;

        if(anetWrite(conn_fd,(char *)package,package_len) < 0) {
            printf("send error ");
        }*/
    }

    zfree(package);
    //close(conn_fd);

    return 0;
}
