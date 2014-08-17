#ifndef Deuterium_NetworkingException_h_
#define Deuterium_NetworkingException_h_

#include <exception>
#include <string>            // For string

namespace Deuterium{

	namespace Networking{

		class NetworkingException : public exception {
		public:
			NetworkingException(const string &message, bool inclSysMsg = false) throw();
			~NetworkingException() throw();	
			const char *what() const throw();
		private:
			std::string userMessage;  // Exception message
		};
	}
}

#endif //File Guardian