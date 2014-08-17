#include "Deuterium::Networking::Socket"
#include "Protium::Collections::List"


using Deuterium::Networking::Socket;
using Deuterium::Networking::TCPSocket;
using Deuterium::Networking::Client;
using Deuterium::DataFormat::StringParser;

int main(int argc, char* argv[]){

	//Enter in the remote address
	std::cout<<"Please Enter Remote Server Address: "<<std::endl;
	std::string address;
	std::cin >> address;

	//Enter in the port(s) which wish to use

	std::cout<<"Please enter a list of ports you wish to use."<<std::endl;
	stc::cout<<"\tDelimit numbers with ',' and ranges with '-'"<<std::endl;

	std::string port_list;
	std::cin >> port_list;
	std:vector<unsigned> ports = StringParser<unsigned>(port_list).delimit(',').makerange('-').AsVector();

	//create the socket
	Socket<TCPSocket, Client> socket;
	socket.SetLocalPort(120);//why not

	for(std::vector<unsigned>::iterator it = ports.begin(); it!= ports.end(); ++it){
		if(scoket.connect(address, (*it) ) )
			std::cout<<"Port: "<<(*it)<<" Open"<<std::endl;
	}
}
