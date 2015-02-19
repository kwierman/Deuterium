#ifndef Deuterium_FileSystem_RootFile_hh_
#define Deuterium_FileSystem_RootFile_hh_

#include "Deuterium/FileSystem/File.hh"
#include "Deuterium/FileSystem/FileUtilities.hh"
#include "Deuterium/FileSystem/ZLib.hh"

#include <iostream>



namespace Deuterium{
   namespace FileSystem{


      struct Record{
         int position_in_file;
         int nBytes; 
         short version;
         int length;
         unsigned datime;
         short keyLen;
         short cycle;
         int seekkey;
         int seekpdir;
         std::string name;
         std::string class_name;
         std::string title;
         std::vector<char> data;

         void Print(){
            std::cout<<position_in_file<<"\t"<<nBytes<<"\t"<<version<<"\t"<<length<<"\t"<<datime<<"\t"<<keyLen<<"\t"<<cycle<<"\t"<<seekkey<<"\t"<<seekpdir<<"\t"<<"\""<<name<<"\""<<"\t"<<"\""<<class_name<<"\""<<"\t"<<"\""<<title<<"\"";
            //for(std::vector<char>::iterator it = data.begin();it!=data.end();++it)
            //   std::cout<<(*it)<<" ";
            std::cout<<std::endl;
         }
      };



      class RootFile : public InputFile{
         int fEnd;

      public:
         bool Read(void* buffer, size_t size ){
            if( eof() ) return false;

            int remainingSize = size;
            char* bufferPtr = reinterpret_cast<char*>(buffer);
            while (remainingSize > 0) {
               fData.read(bufferPtr, remainingSize);
               int readSize = fData.gcount();
               if (readSize > 0) {
                  bufferPtr += readSize;
                  remainingSize -= readSize;
               }
               if ((remainingSize > 0) && fData.eof()) {
                  fData.clear();
                  return false;
               }
            }
            return (remainingSize == 0);
         }


         void Init(){
            PutStreamPosFromBegin(0);
            
            char* root = new char[4];
            Read(root, 4);

            int version;
            Read(&version, 4);
            version = SwapWord(version);
            int begin;
            Read(&begin,4);
            begin=SwapWord(begin);
            Read(&fEnd,4);
            fEnd=SwapWord(fEnd);
            int seekfree;
            Read(&seekfree, 4);
            seekfree=SwapWord(seekfree);
            int nBytesfree;
            Read(&nBytesfree,4);
            nBytesfree=SwapWord(nBytesfree);
            int nfree;
            Read(&nfree, 4);
            nfree=SwapWord(nfree);
            int nBytesname;
            Read(&nBytesname,4);
            nBytesname=SwapWord(nBytesname);
            unsigned char units;
            Read(&units, 1);
            
            int compress;
            Read(&compress, 4);
            int seekinfo;
            Read(&seekinfo, 4);
            int nbytesinfo;
            Read(&nbytesinfo, 4);
            
            unsigned short* uuid1 = new unsigned short[9];
            Read(uuid1, 18);
            PutStreamPosFromBegin(begin);
         }


         void ReadRecord(){
            Record rec;
            rec.position_in_file = StreamPos();
            if(rec.position_in_file==fEnd){
               PutStreamPosFromEnd(0);
               Close();
               return;
            }
            
            Read(&rec.nBytes,4);
            rec.nBytes=SwapWord(rec.nBytes);
            Read(&rec.version, 2);
            rec.version=SwapShort(rec.version);
            Read(&rec.length, 4);
            rec.length=SwapWord(rec.length);
            Read(&rec.datime, 4);
            rec.datime=SwapWord(rec.datime);
            Read(&rec.keyLen, 2);
            rec.keyLen = SwapShort(rec.keyLen);
            Read(&rec.cycle, 2);
            rec.cycle = SwapShort(rec.cycle);
            //At this point, branch to see if 
            if(rec.version<=1000){
               Read(&rec.seekkey, sizeof(int));
               rec.seekkey=SwapWord(rec.seekkey);
               Read(&rec.seekpdir, sizeof(int));
               rec.seekpdir=SwapWord(rec.seekpdir);

               if(rec.seekkey!= rec.position_in_file)
                     std::cout<<"Warning: SeekKey not set to correct position"<<std::endl;

               char lname;
               char name_buffer[512];

               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.class_name=name_buffer;


               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.name=name_buffer;


               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.title=name_buffer;


               //consume data
               int data_length = rec.position_in_file+rec.nBytes -StreamPos();
               char buffer[data_length];
               Read(buffer,data_length);



               for(int i=0; i<data_length;i++)
                  rec.data.push_back(buffer[i] );               
            }
            else{
               long long lBuffer;
               Read(&lBuffer, sizeof(int)*2);
               rec.seekkey=SwapWord(lBuffer);
               Read(&lBuffer, sizeof(int)*2);
               rec.seekpdir=SwapWord(lBuffer);


               //if(rec.seekkey!= rec.position_in_file)
               //      std::cout<<"Warning: SeekKey not set to correct position"<<std::endl;

               char lname;
               char name_buffer[512];

               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.class_name=name_buffer;


               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.name=name_buffer;


               Read(&lname, 1);
               for(int i=0; i<lname;i++)
                  Read(&(name_buffer[i]), 1);
               name_buffer[(int)lname]='\0';
               rec.title=name_buffer;


               rec.Print();
               //consume data
               int data_length = rec.position_in_file+rec.nBytes -StreamPos();
               char buffer[data_length];
               Read(buffer,data_length);



               for(int i=0; i<data_length;i++)
                  rec.data.push_back(buffer[i] );
            }
            
            rec.Print();
            //PutStreamPosFromBegin(rec.position_in_file+rec.nBytes);

         }


      public:
         RootFile(const Path& path) : InputFile(path) {}
         
      };
   }
}



#endif //File Guardian
