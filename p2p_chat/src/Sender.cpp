#include <iostream>
#include "Sender.hh"

Sender::Sender(std::string pseudo, UdpSocket* broadcast)
{
  commandFuncs_["/leave"] = &Sender::leave;
  pseudo_ = pseudo;
  broadcast_ = broadcast;
  keep_ = true;
  local_ = NULL;
  current_ = Sender::TALK;
}

Sender::~Sender()
{
  if (local_)
    delete local_;
}

void Sender::operator()()
{
  local_ = new UdpSocket("127.0.0.1", "13001");
  std::string message;
  std::string joinMessage = "user:" + pseudo_ + "\ncommand:come\n\n";

  broadcast_->send(joinMessage.c_str(), joinMessage.size());
  while (keep_) {
    std::getline(std::cin, message);
    
    buildMessage(message);
  }
}

void Sender::buildMessage(std::string const& message)
{
  size_t idx = message.find_first_of(' ');
  std::string command;
  std::string param;
  if (idx != std::string::npos) {
    command = message.substr(0, idx);
    param = message.substr(idx + 1);
  }
  else {
    command = message;
  }
  if (commandFuncs_.find(command) != commandFuncs_.end()) {
    (this->*commandFuncs_[command])(param);
  }
  else {
    (this->*sendFuncs_[current_])(message);
  }
}

void Sender::leave(std::string const&)
{
  std::string message = "user:" + pseudo_ + "\ncommand:LEAVE\n\n";
  std::string quitMessage = "command:QUIT\n\n";
  
  local_->send(quitMessage.c_str(), quitMessage.size());
  broadcast_->send(message.c_str(), message.size());
  keep_ = false;
}
