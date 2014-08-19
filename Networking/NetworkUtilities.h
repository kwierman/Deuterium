#ifndef Deuterium_NetworkUtilities_h_
#define Deuterium_NetworkUtilities_h_

#include "Deuterium/Networking/NetworkingException.h"

#include <string>

#include <netinet/in.h>      // For sockaddr_in
#include <netdb.h>           // For gethostbyname()
#include <string>
#include <string.h>


namespace Deuterium{
	namespace Networking{
		static void fillAddr(const std::string &address, unsigned short port, sockaddr_in &addr){
  memset(&addr, 0, sizeof(addr) );  // Zero out address structure
  addr.sin_family = AF_INET;       // Internet address

  hostent* host;  // Resolve name
  if ((host = gethostbyname(address.c_str())) == NULL) {
    // strerror() will not work for gethostbyname() and hstrerror() 
    // is supposedly obsolete
    std::string problem = "Failed to resolve name (gethostbyname())";
    problem+=address;
    throw NetworkingException(problem.c_str());
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);     // Assign port in network byte order
}


    static  unsigned short csum(unsigned short *buf, int len){

        unsigned long sum;

        for(sum=0; len>0; len--)

                sum += *buf++;

        sum = (sum >> 16) + (sum &0xffff);

        sum += (sum >> 16);

        return (unsigned short)(~sum);
    }
  }
}



#endif //File Guardian