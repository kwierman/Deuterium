#ifndef Deuterium_NetworkUtilities_h_
#define Deuterium_NetworkUtilities_h_

#include <string>

#include <netinet/in.h>      // For sockaddr_in

namespace Deuterium{
	namespace Networking{

		static void fillAddr(const std::string &address, unsigned short port, sockaddr_in &addr);
	}

}



#endif //File Guardian