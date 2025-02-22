#include <stdlib.h>

#include "newnode.h"
#include "network.h"
#include "thread.h"
#include "log.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

void ui_display_stats(const char *type, uint64_t direct, uint64_t peers) {}

int main(int argc, char *argv[])
{
    char *port_s = "8006";

    for (;;) {
        int c = getopt(argc, argv, "p:v");
        if (c == -1) {
            break;
        }
        switch (c) {
        case 'p':
            port_s = optarg;
            break;
        case 'v':
            o_debug++;
            break;
        default:
            log_error("Unhandled argument: %c\n", c);
            return 1;
        }
    }

    port_t port = atoi(port_s);
    network *n = newnode_init("client", "com.newnode.client", &port, ^(const char *url, https_complete_callback cb) {
        debug("https: %s\n", url);
        cb(true);
    });
    if (!n) {
        return 1;
    }

#ifdef __APPLE__
    newnode_thread(n);
    CFRunLoopRun();
    return 0;
#else
    return newnode_run(n);
#endif
}
