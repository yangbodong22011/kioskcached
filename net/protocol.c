#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "define.h"
#include "Item.h"
#include "Kioskcached.h"
#include "Kiosktime.h"
#include<gperftools/profiler.h>

extern Kioskcached kio;
extern Timer t;

package_t *alloc_packet(uint32_t data_len)
{
    package_t *package = (package_t*)zmalloc(sizeof(package_head_t) + data_len);

    if (package) {
        package->head.magic = MAGIC_NUMBER;
        package->head.length = data_len;
    }

    return package;
}

void free_package(package_t *package)
{
    zfree(package);
}

int packet_decode(buffer_t *buffer, package_t **package)
{
    size_t data_len = get_readable_size(buffer);
    if (data_len < sizeof(package_head_t)) {
        return -1;
    }
    package_head_t *package_head = (package_head_t *)(buffer->buff + buffer->read_idx);
    if (package_head->magic != MAGIC_NUMBER) {
        return -2;
    }

    size_t package_len = sizeof(package_head_t) + package_head->length;
    if (data_len < package_len) {
        return -1;
    }

    package_t *new_package = (package_t*)zmalloc(package_len);
    memcpy(new_package, buffer->buff + buffer->read_idx, package_len);
    buffer->read_idx += package_len;

    *package = new_package;

    return 0;
}

int package_encode(buffer_t *buffer, package_t *package)
{
    size_t avlid_size = get_writeable_size(buffer);
    size_t package_len = sizeof(package_head_t) + package->head.length;

    if (avlid_size < package_len) {
        return -1;
    }

    memcpy(buffer->buff + buffer->write_idx, package, package_len);
    buffer->write_idx += package_len;

    return 0;
}

void do_package(package_t *req_package, package_t **resp_package)
{
    static int n = 0;
    if(n == 999999) {
        printf("n : %d\n",n);
        std::cout << (1.0 * 1000000) / (1.0 * t.elapsed_micro() / 1000 /1000 ) << " QPS" << std::endl;
        ProfilerStop();
        exit(0);
    }
    const char * const name = "hurley";
    char key[256] = {0};
    switch (req_package->head.type) {
        case QUERY_NAME:
            *resp_package = alloc_packet((uint32_t)strlen(name) + 1);
            if (*resp_package) {
                memcpy((*resp_package)->data, name, strlen(name) + 1);
            } else {
                printf("alloc package error, OOM ?");
            }
            break;
        case CHAT_MESSAGE:
            printf("chat message: No.%d %s\n", n++, req_package->data);
            break;
        case KIO_SET:
            snprintf(key,sizeof(key),"%0*d",100,n);
            //printf("req_package-head.length : %d\n",req_package->head.length);    

            ItemPtr item(Item::makeItem(key,0,0,req_package->head.length+sizeof(package_head_t)+2,1));
            item->append((const char *)req_package->data,(size_t)req_package->head.length);
            item->append("\r\n",(size_t)2);
            
            kio.storeItem(item,Item::kAdd,1);
            //printf("key: No.%d %s %s\n", n,key,req_package->data);
            ++n;
            break;
    }
}
