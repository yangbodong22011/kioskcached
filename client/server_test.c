#include "anet.h"
#include "define.h"
#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int items = argc > 1 ? atoi(argv[1]) : 1000;
    int valuelen = argc > 2 ? atoi(argv[2]) : 100;

    char err[ANET_ERR_LEN];
    int conn_fd = anetTcpConnect(err, "127.0.0.1", DEFAULT_LISTEN_PORT);
    if (conn_fd == ANET_ERR) {
        printf("connect error: %s\n", err);
        return -1;
    }
    
    char *send_info = (char *)malloc(valuelen);
    
    for(int i = 0;i < valuelen;++i) {
        send_info[i] = 'a';
    }
    char send_buff[1024];
    snprintf(send_buff, sizeof(send_buff), "%s",send_info);

    package_t *package = alloc_packet((uint32_t)strlen(send_buff) + 1);
    package->head.type = KIO_SET;
    // copy with '\0'
    memcpy(package->data, send_buff, strlen(send_buff) + 1);

    int package_len = sizeof(package_head_t) + package->head.length;

    printf("send package size: %d\n", package_len);
    for (int i = 0; i < items; ++i) {
        if (anetWrite(conn_fd, (char *)package, package_len) < 0) {
            printf("send error, exit.");
        }
    }

    /*printf("slow send ...\n");
    for (int i = 0; i < items; ++i) {
        if (anetWrite(conn_fd, (char *)package, package_len) < 0) {
            printf("send error, exit.");
        }
        usleep(10000);
    }

    printf("more slow send ...\n");
    for (int n = 0; n < items; ++n) {
        for (int i = 0; i < package_len; ++i) {
            if (anetWrite(conn_fd, (char *) package + i, 1) < 0) {
                printf("send error, exit.");
            }
            usleep(10000);
        }
    }*/

    zfree(package);
    close(conn_fd);

    return 0;
}
