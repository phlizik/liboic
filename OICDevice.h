#ifndef OICDEVICE_H
#define OICDEVICE_H

#include <string>
#include <vector>
#include "COAPPacket.h"
#include "COAPServer.h"


using namespace std;

class OICClient;
class OICDeviceResource;

class OICDevice
{
public:
    OICDevice(string id, string name, string address, OICClient* client);

    vector<OICDeviceResource*>* getResources() { return &m_resources;}

    string getAddress() { return m_address; }

    string getId() { return m_id; }
    string getName() { return m_name;}

    void send(COAPPacket* packet, COAPResponseHandler func);

private:
    string m_id;
    string m_name;
    string m_address;
    OICClient* m_client;
    vector<OICDeviceResource*> m_resources;
};

#endif // OICDEVICE_H
