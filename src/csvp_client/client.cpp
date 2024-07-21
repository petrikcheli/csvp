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
        std::cerr << "Failed create socket" << std::endl;
        closesocket(socket_server); // Закрытие сокета при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    } else {
        std::cerr << "Managed to create socket" << std::endl;
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
        std::cerr << "Error connect to server" << std::endl;
        return -1;
    }

    return 0; // Успешное подключение
}

// Метод для отправки координат героя серверу
int Client::send_command(struct Game::Player& command){
    if(send(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Failed send command to server" << std::endl;
        return -1;
    }
    return 0; // Успешная отправка команды
}

// Метод для отправки массива пуль героя
int Client::send_command(struct Game::BulletManager& command){

    // Сначала отправляем размер массива
    Size_Bullets size;
    size.size = command.bullets.size();
    if(send(socket_server, (char *)&size.size, sizeof(int), 0) < 0){
        std::cerr << "Failed to send sizeof to client" << std::endl;
        return -1;
    }

    // Поочередно отправляем массив пуль
    for(int i = 0; i < size.size; i++){
        if(send(socket_server, (char *)&command.bullets[i], sizeof(struct Game::Bullet), 0) < 0){
            std::cerr << "Failed to send bullet with index " << i << std::endl;
            return -1;
        }
    }

    return 0; // Успешная отправка команды
}

// Метод для получения координат противника от сервера
int Client::recv_command(struct Game::Player& command){
    if(recv(socket_server, (char *)&command, sizeof(command), 0) < 0){
        std::cerr << "Failed to receive message" << std::endl;
        return -1;
    }
    return 0; // Успешное получение команды
}

// Метод для получения массива пуль противника
int Client::recv_command(struct Game::BulletManager& command){
    // Сначала получаем размер массива пуль
    Size_Bullets size;
    if(recv(socket_server, (char *)&size, sizeof(size), 0) < 0){
        std::cerr << "Failed to receive sizeof from client" << std::endl;
        return -1;
    }

    // Меняем размер массива
    command.bullets.resize(size.size);

    // Поочередно получаем пули и записываем их в массив
    for(int i = 0; i < size.size; i++){
        if(recv(socket_server, (char *)&command.bullets[i], sizeof(struct Game::Bullet), 0) < 0){
            std::cerr << "Failed to receive bullet with index " << i << std::endl;
            return -1;
        }
    }
    return 0; // Успешное получение команды
}

// Метод для закрытия сокета и освобождения ресурсов
void Client::close_socket(){
    shutdown(socket_server, 2); // Завершение работы сокета
    closesocket(socket_server); // Закрытие сокета
    WSACleanup(); // Освобождение ресурсов Windows Sockets
}
