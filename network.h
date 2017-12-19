#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/dns.h>
#include <event2/http.h>
#include <event2/http_struct.h>

#include "utp.h"

typedef struct network network;

#include "dht.h"


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define PACKED __attribute__((__packed__))
#define lenof(x) (sizeof(x)/sizeof(x[0]))
#define alloc(type) calloc(1, sizeof(type))
#define memeq(a, b, len) (memcmp(a, b, len) == 0)
#define memdup(m, len) memcpy(malloc(len), m, len)


typedef struct event_base event_base;
typedef struct evdns_base evdns_base;
typedef struct event event;
typedef struct evhttp evhttp;
typedef struct evbuffer evbuffer;
typedef struct evutil_addrinfo evutil_addrinfo;
typedef struct bufferevent bufferevent;
typedef struct addrinfo addrinfo;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_in6 sockaddr_in6;
typedef struct sockaddr_storage sockaddr_storage;
typedef in_port_t port_t;

#include "timer.h"


struct network {
    event_base *evbase;
    evdns_base *evdns;
    int fd;
    event udp_event;
    utp_context *utp;
    dht *dht;
    timer *dht_timer;
    evhttp *http;
};

void evbuffer_clear(evbuffer *buf);
network* network_setup(char *address, port_t port);
int network_loop(network *n);

#endif // __NETWORK_H__
