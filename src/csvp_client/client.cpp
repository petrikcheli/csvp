#include "client.h"

// Конструктор клиента, здесь можно инициализировать необходимые переменные
Client::Client()
{

}

// Деструктор клиента, вызывается при удалении объекта
Client::~Client(){
    close_socket(); // Закрытие сокета и освобождение ресурсов
}

// Метод для старта клиента, создается сокет
int Client::start_client()
{
    socket_server = socket(AF_INET, SOCK_STREAM, 0);

    // Проверка успешности создания сокета
    if(socket_server == INVALID_SOCKET){
        std::cout << "Ошибка создания сокета" << std::endl;
        closesocket(socket_server); // Закрытие сокета при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    } else {
        std::cout << "Сокет успешно создан" << std::endl;
    }

    // Настройка параметров сервера
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT_SERVER); // Указываем порт
    addr_server.sin_addr.s_addr = inet_addr(IP_SERVER); // Указываем IP-адрес

    // Закомментированный код для привязки сокета к порту и IP-адресу
    // if(bind(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) != 0){
    //     std::cout << "Не удалось связать порт и IP с сокетом" << std::endl;
    //     closesocket(socket_server);
    //     WSACleanup();
    //     return -1;
    // } else {
    //     std::cout << "Порт и IP успешно связаны с сокетом" << std::endl;
    // }

    return 0; // Успешное завершение метода
}

// Метод для подключения к серверу
int Client::connect_to_server(){
    if(connect(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server))<0){
        std::cout << "Ошибка подключения к серверу" << std::endl;
        return -1;
    }

    return 0; // Успешное подключение
}

// Метод для отправки команды серверу
int Client::send_command(struct Game::Player& command){
    if(send(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Ошибка отправки команды серверу" << std::endl;
        return -1;
    }
    return 0; // Успешная отправка команды
}

// Метод для получения команды от сервера
int Client::recv_command(struct Game::Player& command){
    if(recv(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Ошибка получения команды от сервера" << std::endl;
        return -1;
    }
    return 0; // Успешное получение команды
}

// Метод для закрытия сокета и освобождения ресурсов
void Client::close_socket(){
    shutdown(socket_server, 2); // Завершение работы сокета
    closesocket(socket_server); // Закрытие сокета
    WSACleanup(); // Освобождение ресурсов Windows Sockets
}
