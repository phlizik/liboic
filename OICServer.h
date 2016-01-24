#ifndef OICSERVER_H
#define OICSERVER_H

#include "pthread.h"
#include <stdint.h>
#include "OICResource.h"
#include "cbor.h"
#include <netinet/in.h>

typedef void(*OICServerSendData)(uint8_t*, uint16_t);

class OICResource;


class OICServer
{
public:
    OICServer();

    void start(string ip, string interface);
    void stop();
    void addResource(OICResource* res) {res->setCoapServer(&coap_server); m_resources.push_back(res);}

    void send(string destination, COAPPacket* packet, COAPResponseHandler func);
    void send(sockaddr_in6 destination, COAPPacket* packet, COAPResponseHandler func);
    COAPServer* getCoapServer() { return &coap_server; }

    int  getSocketFd() { return m_socketFd; }
    void setSocketFd(int socket) { m_socketFd = socket; }
private:
    string convertAddress(sockaddr_in6 addr);
    static void* run(void*param);
    static void* runDiscovery(void*param);
    bool onRequest(COAPServer* server, COAPPacket* request, COAPPacket* response);
    bool discoveryRequest(COAPServer* server, COAPPacket* request, COAPPacket* response);

    OICResource* getResource(string href);

    pthread_t m_thread;
    pthread_t m_discoveryThread;

    uint8_t buffer[1024];
    COAPServer coap_server;
    vector<OICResource*> m_resources;
    int m_socketFd;
};

#endif // OICSERVER_H