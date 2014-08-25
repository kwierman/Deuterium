

int main(int argc, char* argv[]){

	if(argc<2){
		std::cout<<"Usage: deuterium_input_test <filename>"<<std::endl;
		return -1;
	}

	//Try out specific 
	Deuterium::FileSystem::File input(argv[1]);
	if(! input.IsValid() ){
		std::cout<<"Invalid filename"<<std::endl;
	}

	Deuterium::DataFormat::Parser<Deuterium::DataFormat::DOMParser> parser(input);
	parser.Read();



}