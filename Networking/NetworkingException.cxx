#include "Deuterium/Networking/NetworkingException.h"


Deuterium::Networking::NetworkingException::NetworkingException(const string &message, bool inclSysMsg)
  throw() : userMessage(message) {
  if (inclSysMsg) {
    userMessage.append(": ");
    userMessage.append(strerror(errno));
  }
}

Deuterium::Networking::NetworkingException::~NetworkingException() throw() {
}

const char* Deuterium::Networking::NetworkingException::what() const throw() {
  return userMessage.c_str();
}