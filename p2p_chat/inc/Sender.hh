#pragma once
#include <string>
#include <map>
#include "UdpSocket.hh"

class Sender {
public:
  Sender(std::string pseudo, UdpSocket* broadcast);
  ~Sender();

  void operator()();
private:
  enum MessageType {
    TALK
  };
  void buildMessage(std::string const& message);

  void leave(std::string const& param);
  typedef void (Sender::*command_)(std::string const& param);
  std::map<std::string, command_> commandFuncs_;

  void sendTalk(std::string const& message);
  typedef void (Sender::*send_)(std::string const& message);
  std::map<MessageType, send_> sendFuncs_;
  
  UdpSocket* broadcast_;
  UdpSocket* local_;

  std::string pseudo_;
  MessageType current_;
  bool keep_;
};
