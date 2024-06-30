#include "client.h"

Client::Client()
{

}

Client::~Client(){
    close_socket();
}

int Client::start_client()
{

    socket_server = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_server == INVALID_SOCKET){
        std::cout << "Failed to create socket" << std::endl;
        closesocket(socket_server);
        WSACleanup();
        return -1;
    } else {
        std::cout << "Managed to create a socket" << std::endl;
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT_SERVER);
    addr_server.sin_addr.s_addr = inet_addr(IP_SERVER);


//    if(bind(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) != 0){
//        std::cout << "Не удалось связять port и ip с socket" << std::endl;
//        closesocket(socket_server);
//        WSACleanup();
//        return -1;
//    } else {
//        std::cout << "port и ip связаны с socket" << std::endl;
//    }

    return 0;
}

int Client::connect_to_server(){
    if(connect(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server))<0){
        std::cout << "Failed to connect to server" << std::endl;
        return -1;
    }

    return 0;
}

int Client::send_command(struct Command& command){
    if(send(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Failed to send command to client" << std::endl;
        return -1;
    }
    return 0;
}

int Client::recv_command(struct Command& command){
    if(recv(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Failed to accept command from server" << std::endl;
        return -1;
    }
    return 0;
}

void Client::close_socket(){
    shutdown(socket_server, 2);
    closesocket(socket_server);
    WSACleanup();
}
