#include <iostream>
#include <cstdio>
#include <enet/enet.h>

/*

SERVER and CLIENT example:
http://lists.cubik.org/pipermail/enet-discuss/2011-March/001697.html

*/

#define PORT 1234
#define MAX_CLIENTS 32

int main(int argc, char ** argv)
{
    system("title SERWER");

    if(enet_initialize() != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    ENetAddress address;
    ENetHost * server;

    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;

    /* Bind the server to port 1234. */
    address.port = PORT;
    server = enet_host_create(&address       /* the address to bind the server host to */,
                              MAX_CLIENTS    /* allow up to 32 clients and/or outgoing connections */,
                              2              /* allow up to 2 channels to be used, 0 and 1 */,
                              0              /* assume any amount of incoming bandwidth */,
                              0              /* assume any amount of outgoing bandwidth */);
    if(server == NULL)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }

    ENetEvent event;
    int serviceResult = 1;

    printf("\nSERVER START\n");

    while(1)
    {
        serviceResult = 1;

        while(serviceResult > 0)
        {
            /* Wait up to 1000 milliseconds for an event. */
            serviceResult = enet_host_service(server, &event, 1000);

            /*if(serviceResult <= 0)
            {
                puts("Error with servicing the server");
                exit(EXIT_FAILURE);
            }*/

            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    printf ("\nA new client connected from %x:%u.\n",
                            event.peer -> address.host,
                            event.peer -> address.port);
                    /* Store any relevant client information here. */
                    event.peer -> data = (void*)"Client information";

                    //message = "Hello my friend :D";
                    //ENetPacket *packet = enet_packet_create (message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                    //enet_peer_send(event.peer, 0, packet);
                }
                break;

                case ENET_EVENT_TYPE_RECEIVE:
                {
                    printf ("\nDOSTANO: '%s', client [%s], kanal [%u].",
                            //event.packet -> dataLength,
                            event.packet -> data,
                            event.peer -> data,
                            event.channelID);

                    //if(event.packet->data == (char*)"KLAWISZ_UP") {
                    //if(strcmp((char*)event.packet->data, "KLAWISZ_UP"))
                    //    std::cout << "\nKLIENT nacisnal UP";
                    //int l;
                    //std::string data;
                    //sscanf((char*)event.packet->data, "%d %s", &l, data);

                    //if(data == "KLAWISZ_UP")
                    //    std::cout << "\nKLIENT nacisnal klawisz up";


                    /// wiadomosc do wszystkich:
                    //enet_host_broadcast(server, 0, event.packet);

                    enet_packet_destroy (event.packet);
                }
                break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf ("\n%s disconected.\n", event.peer -> data);
                    /* Reset the peer's client information. */
                    event.peer -> data = NULL;
                break;
            }
        }

    }//while(1)

    atexit(enet_deinitialize);
    enet_host_destroy(server);
}
