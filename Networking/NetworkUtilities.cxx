#include "Deuterium/Networking/NetworkUtilities.h"
#include "Deuterium/Networking/NetworkingException.h"

#include <netdb.h>           // For gethostbyname()
#include <string>
#include <string.h>

// Function to fill in address structure given an address and port
static void Deuterium::Networking::fillAddr(const std::string& address, unsigned short port, sockaddr_in &addr) {
  memset(&addr, 0, sizeof(addr) );  // Zero out address structure
  addr.sin_family = AF_INET;       // Internet address

  hostent* host;  // Resolve name
  if ((host = gethostbyname(address.c_str())) == NULL) {
    // strerror() will not work for gethostbyname() and hstrerror() 
    // is supposedly obsolete
    throw NetworkingException("Failed to resolve name (gethostbyname())");
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);     // Assign port in network byte order
}