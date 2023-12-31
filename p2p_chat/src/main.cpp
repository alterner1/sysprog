#include <iostream>
#include <thread>

#include <unistd.h>
#include <fcntl.h>

#include "Receiver.hh"
#include "Sender.hh"

int main(int ac, char** av)
{
  if (ac != 2) {
    std::cerr << "usage: chat ip_address (on port 13001) " << std::endl;
    return 1;
  }
  std::string pseudo;
  std::cout << "Enter your name : ";
  std::getline(std::cin, pseudo);

  UdpSocket* broadcast = new UdpSocket(av[1], "13001");
  std::thread* receiver = new std::thread(Receiver(pseudo, broadcast));
  std::thread* sender = new std::thread(Sender(pseudo, broadcast));

  receiver->join();
  sender->join();
  return 0;
}
