#ifndef Deuterium_FileSystem_Path_hh_
#define Deuterium_FileSystem_Path_hh_

#include "Deuterium/FileSystem/FileUtilities.hh"

#include <string>
#include <vector>
#include <sstream>



namespace Deuterium{
	namespace FileSystem{


		class Path{
			std::string fName;

		public:

			//! name can be a relative path or an absolute path.
			Path(const std::string& name) : fName(name) {}
			Path(const char* name) : fName(name) {}
			Path(const Path& other) : fName(other.fName) {}

			static Path CWD(){
				return Path(cwd());
			}

			//the other path must be 
			Path& operator+=(const Path& other){
				this->fName+=other.fName;
				this->simplifyPath();
				return *this;
			}

			Path operator+(const Path& other){
				Path output(*this);
				output+=other;
				return output;
			}


			std::string GetName() const{
				return fName;
			}

			//! Get back the absolute path
			std::string GetAbsolutePath(){

				if(this->fName.at(0) == '/' ){
					return fName;
				}
				std::string temp = fName;
				fName = cwd();
				fName+="/";
				fName+=temp;
				return fName;
			}

			std::string simplifyPath(){
				std::vector<std::string> path;
				std::stringstream input(fName);
				std::string segment;
				while(std::getline(input, segment, '/')){
					if(segment.size() || segment != std::string(" ") )
							path.push_back(segment);
				}

				typedef std::vector<std::string>::iterator tokit;
				std::string here = ".";
				std::string before = "..";

				for(tokit it = path.begin(); it!=path.end(); ++it){
					if( (*it) ==  here){
						path.erase(it);
						it = path.begin();
						}
					else if( (*it) == before ){
						tokit retstatement = it;
						tokit tobeerased = it;
						path.erase(--tobeerased);
						path.erase(retstatement);
						it = path.begin();
					}
				}
				fName="";
				std::stringstream outbuffer;
				for(tokit it = path.begin(); it!=path.end(); ++it)
					if( (*it).size()>0 )
						outbuffer<<"/"<< std::string(*it);
				outbuffer>>fName;
				return fName;
			}

		};

	}
}



#endif //Fie Guardian
