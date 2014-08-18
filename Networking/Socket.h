#ifndef Deuterium_Socket_h_
#define Deuterium_Socket_h_
#include "Deuterium/Networking/NetworkingException.h"


namespace Deuterium{
  namespace Networking{
    
    class SocketPrototype{
      ~SocketPrototype();
      std::string GetLocalAddress() throw(NetworkingException);
      unsigned GetLocalPort() throw(NetworkingException);
      void SetLocalPort(unsigned localPort) throw(NetworkingException);
      void setLocalAddressAndPort(const std::string &localAddress, unsigned short localPort = 0) throw(NetworkingException);
      static unsigned short resolveService(const std::string& service,const std::string& protocol="tcp");
    private:
      SocketPrototype(const SocketPrototype&);
      void operator=(const SocketPrototype&);
    protected:
      int sockDesc;
      SocketPrototype(int type, int protocol) throw(NetworkingException);
      SocketPrototype(int sockDesc);
    };

    class ConcreteSocket : public SocketPrototype {
    public:
      void connect(const std::string &foreignAddress, unsigned short foreignPort) throw(NetworkingException);
      void send(const void *buffer, int bufferLen) throw(NetworkingException);
      int recv(void *buffer, int bufferLen) throw(NetworkingException);
      std::string getForeignAddress() throw(NetworkingException);
      unsigned short getForeignPort() throw(NetworkingException);

    protected:
      ConcreteSocket(int type, int protocol) throw(NetworkingException);
      ConcreteSocket(int newConnSD);
    };

    class TCPClientSocket : public ConcreteSocket{
      TCPClientSocket() throw(NetworkingException);
      TCPClientSocket(const std::string &foreignAddress, unsigned short foreignPort) throw(NetworkingException);

    private:
      //friend class TCPServerSocket;
      TCPClientSocket(int newConnSD);
    };
  }
}

#endif //File Guardian

/*
class TCPServerSocket : public Socket {
public:
  TCPServerSocket(unsigned short localPort, int queueLen = 5) 
      throw(SocketException);
  TCPServerSocket(const string &localAddress, unsigned short localPort,
      int queueLen = 5) throw(SocketException);
  TCPSocket *accept() throw(SocketException);

private:
  void setListen(int queueLen) throw(SocketException);
};
class UDPSocket : public CommunicatingSocket {
public:
  UDPSocket() throw(SocketException);
  UDPSocket(unsigned short localPort) throw(SocketException);
  UDPSocket(const string &localAddress, unsigned short localPort) 
      throw(SocketException);
  void disconnect() throw(SocketException);

  void sendTo(const void *buffer, int bufferLen, const string &foreignAddress,
            unsigned short foreignPort) throw(SocketException);
  int recvFrom(void *buffer, int bufferLen, string &sourceAddress, 
               unsigned short &sourcePort) throw(SocketException);

  void setMulticastTTL(unsigned char multicastTTL) throw(SocketException);

  void joinGroup(const string &multicastGroup) throw(SocketException);

  void leaveGroup(const string &multicastGroup) throw(SocketException);

private:
  void setBroadcast();
};

*/