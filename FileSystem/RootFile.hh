#ifndef Deuterium_FileSystem_RootFile_hh_
#define Deuterium_FileSystem_RootFile_hh_

#include "Deuterium/FileSystem/File.hh"
#include "Deuterium/FileSystem/FileUtilities.hh"
#include "Deuterium/Compression/zlib.hh"

#include "Deuterium/FileSystem/Order32.hh"

#include <iostream>
//Bear in mind that ROOT files are always Big Endian


namespace Deuterium{
   namespace FileSystem{
      template<typename XType>
      struct AsString{
         std::string operator()(const XType& other){
            //this should be a lexical cast
            std::stringstream ss;
            ss << other;
            return ss.str();
         }
      };

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
         std::vector<unsigned char> data;

         void Print(){
            std::cout<<position_in_file<<"\t"<<nBytes<<"\t"<<version<<"\t"<<length<<"\t"<<DateTimeFormat()<<"\t"<<keyLen<<"\t"<<cycle<<"\t"<<seekkey<<"\t"<<seekpdir<<"\t"<<"\""<<name<<"\""<<"\t"<<"\""<<class_name<<"\""<<"\t"<<"\""<<title<<"\"";
            /*for(std::vector<unsigned char>::iterator it = data.begin();it!=data.end();++it){
                              std::cout<<(*it)<<" ";
            }*/
            std::cout<<std::endl;
         }
         std::string DateTimeFormat(){
            std::string output;
            unsigned year  = datime>>26;
            unsigned month = (datime<<6)>>28;
            unsigned day   = (datime<<10)>>27;
            unsigned hour  = (datime<<15)>>27;
            unsigned min   = (datime<<20)>>26;
            unsigned sec   = (datime<<26)>>26;
            AsString<unsigned> converter;
            output+=converter(1995+year);
            output+="/";
            output+=converter(month);
            output+="/";
            output+=converter(day);
            output+=" ";
            output+=converter(hour);
            output+=":";
            output+=converter(min);
            output+=":";
            output+=converter(sec);

            return output;
         }

      };

      struct TObject{
        unsigned uniqueID;
        unsigned bits;
        //takes the input buffer, reads the class info starting from the offset, and returns the number of bytes read (and therefore which can be popped off)
        size_t Read(std::vector<unsigned char>& buffer, const size_t& offset){
          return 0;
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




            }

            //consume data
            int data_length = rec.position_in_file+rec.nBytes -StreamPos();
            unsigned char buffer[data_length];
            Read(buffer,data_length);

            bool init=false;
            for(int i=0; i<data_length;i++){
                  rec.data.push_back(buffer[i] );
            }


               //std::cout<<"Object Version: "<<version_of_object<<std::endl;
            rec.Print();
            //PutStreamPosFromBegin(rec.position_in_file+rec.nBytes);
            if(rec.class_name=="TFile"){
               ReadTFileRecord(rec);
            }
            else if(rec.class_name=="TBasket"){
               ReadTBasketRecord(rec);
            }
            else if(rec.class_name=="TH1F"){
              ReadTH1FRecord(rec);
            }

         }


         template<typename XType>
         XType ConvertBuffer(std::vector<unsigned char>& buffer,const size_t& position=0, const bool& swap =false){
          union {
            XType          ret;
            unsigned char  cs[sizeof(XType)];
          } converter;

          for(int i=0;i<sizeof(XType);i++)
            converter.cs[i] = swap?  buffer[position+sizeof(XType)-i] : buffer[position+i];
          return converter.ret;
         }


         int unzip_header(int *srcsize, unsigned char* src, int *tgtsize){
           // Reads header envelope, and determines target size.
           // Returns 0 in case of success.

           *srcsize = 0;
           *tgtsize = 0;

           /*   C H E C K   H E A D E R   */
           if (!(src[0] == 'Z' && src[1] == 'L' && src[2] == Z_DEFLATED) &&
               !(src[0] == 'C' && src[1] == 'S' && src[2] == Z_DEFLATED) &&
               !(src[0] == 'X' && src[1] == 'Z' && src[2] == 0)) {
             return 1;
           }

           *srcsize = 9 + ((long)src[3] | ((long)src[4] << 8) | ((long)src[5] << 16));
           *tgtsize = (long)src[6] | ((long)src[7] << 8) | ((long)src[8] << 16);

           return 0;
         }

         int unzip(int *srcsize, unsigned char *src, int *tgtsize, unsigned char *tgt, int *irep){
           long isize;
           unsigned char* ibufptr,*obufptr;
           long  ibufcnt, obufcnt;

           *irep = 0L;

           /*   C H E C K   H E A D E R   */

           if (*srcsize < 9) {
             std::cout<<"R__unzip: too small source"<<std::endl;
             return 0;
           }

           /*   C H E C K   H E A D E R   */
           if (!(src[0] == 'Z' && src[1] == 'L' && src[2] == Z_DEFLATED) &&
               !(src[0] == 'C' && src[1] == 'S' && src[2] == Z_DEFLATED) &&
               !(src[0] == 'X' && src[1] == 'Z' && src[2] == 0)) {
             std::cout<<"Error R__unzip: error in header"<<std::endl;
             return 0;
           }

           ibufptr = src + 9;
           ibufcnt = (long)src[3] | ((long)src[4] << 8) | ((long)src[5] << 16);
           isize   = (long)src[6] | ((long)src[7] << 8) | ((long)src[8] << 16);
           obufptr = tgt;
           obufcnt = *tgtsize;

           if (obufcnt < isize) {
             std::cout<<"R__unzip: too small target"<<std::endl;
             return 0;
           }

           if (ibufcnt + 9 != *srcsize) {
             std::cout<<"R__unzip: discrepancy in source length"<<std::endl;
             return 0;
           }

           /*   D E C O M P R E S S   D A T A  */

           /* New zlib format */
           if (src[0] == 'Z' && src[1] == 'L') {
             z_stream stream; /* decompression stream */
             int err = 0;

             stream.next_in   = (Bytef*)(&src[9]);
             stream.avail_in  = (uInt)(*srcsize);
             stream.next_out  = (Bytef*)tgt;
             stream.avail_out = (uInt)(*tgtsize);
             stream.zalloc    = (alloc_func)0;
             stream.zfree     = (free_func)0;
             stream.opaque    = (voidpf)0;

             err = inflateInit(&stream);
             if (err != Z_OK) {
               std::cout<<"R__unzip: error %d in inflateInit (zlib)\n"<<std::endl;
               return 0;
             }

             err = inflate(&stream, Z_FINISH);
             if (err != Z_STREAM_END) {
               inflateEnd(&stream);
               std::cout<<"R__unzip: error %d in inflate (zlib)\n"<<std::endl;;
               return 0;
             }

             inflateEnd(&stream);

             *irep = stream.total_out;
             return 0;
           }


           /* if (obufptr - tgt != isize) {
             There are some rare cases when a few more bytes are required */
           if (obufptr - tgt > *tgtsize) {
             //std::cout<<"R__unzip: discrepancy (%ld) with initial size: %ld, tgtsize=%d\n",
              //       (long)(obufptr - tgt),isize,*tgtsize);
             *irep = obufptr - tgt;
             return 0;
           }

           *irep = isize;
         }

         std::vector<unsigned char> decompress(std::vector<unsigned char>& input, size_t length){
            std::vector<unsigned char> out;

            int nin, nbuf,nout;
            int ret_value = unzip_header(&nin, &(input[19]),&nbuf );
            out.resize(nbuf);
            ret_value = unzip(&nin, &(input[19]), &nbuf, &(out[0]), &nout);


            //std::cout<<"Header unzip returned: "<<ret_value<<std::endl;
            //if(ret_value==0)
               //return out
            /*

            */

            return out;
         }

         std::vector<unsigned char> decompress_alt(std::vector<unsigned char>& input, size_t length){
            std::cout<<"Decompressing record..."<<std::endl;
            int ret;
            unsigned have;
            std::vector<unsigned char> out;

            out.resize(length);

            z_stream strm;
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;
            strm.avail_in = 0;
            strm.next_in = Z_NULL;
            ret = inflateInit(&strm);
            if (ret != Z_OK){
               std::cout<<"Could not initialize decompression stream"<<std::endl;
               return out;
            }
            strm.avail_in = input.size();
            strm.next_in = (unsigned char*)&(input[0]);
            strm.avail_out=length;
            strm.next_out= (unsigned char*)&(out[0]);
            ret=inflate(&strm, Z_NO_FLUSH);
            (void)inflateEnd(&strm);
         }

         void ReadTObjectRecord(Record& rec){
           std::cout<<"Unique ID: "<<ConvertBuffer<unsigned>(rec.data,0) <<std::endl;
           std::cout<<"Flag Bits: "<<ConvertBuffer<unsigned>(rec.data,4) <<std::endl;
         }


         void ReadTFileRecord(Record& rec){

            std::cout<<"\tTFile Version: "<<rec.version<<std::endl;

            /*std::cout<<"TFile Record: "<<rec.data.size()<<std::endl<<"\t";
            std::vector<unsigned> dat_list;
            for(int i=0; i<rec.data.size();i+=2){
               unsigned newDat = rec.data[i];
               std::cout<<newDat<<" ";
               dat_list.push_back(newDat);
            }
            std::cout<<std::endl;
            */
         }




         void ReadTBasketRecord(Record& rec){
            std::vector<unsigned char> decompressed_data = rec.data;
            while(decompressed_data.size()<rec.length){
               decompressed_data = decompress(decompressed_data, rec.length);
               if(decompressed_data.size()==0)
                  return;
            }
            int position = 0;

            unsigned bytecount = ConvertBuffer<unsigned>(decompressed_data, 0);

            short ver1 = (ConvertBuffer<short>(decompressed_data,position) ) ;
            std::cout<<"Version: "<<ver1<<std::endl;
            position+=2;

            unsigned checksum = Swap4Bytes<unsigned>(ConvertBuffer<unsigned>(decompressed_data,position+=2) ) ;
            std::cout<<"CheckSum: "<<checksum<<std::endl;

            int buffer_size = Swap4Bytes<int>(ConvertBuffer<int>(decompressed_data,position+=4) );
            int nevBuffSize = Swap4Bytes<int>(ConvertBuffer<int>(decompressed_data,position+=4) );
            int nevBuff     = Swap4Bytes<int>(ConvertBuffer<int>(decompressed_data,position+=4) );
            int last        = Swap4Bytes<int>(ConvertBuffer<int>(decompressed_data,position+=4) );
            char flag       = ConvertBuffer<char>(decompressed_data,26);

            std::cout<<"\tTBasket Buffer Size: "<<buffer_size<<" nevBuffSize: "<<nevBuffSize<<
            " nevBuff: "<<nevBuff<<" last: "<<last<<" flag: "<<(int)flag<<std::endl;
            return;
         }

         void ReadTAxisRecord(Record& rec){

         }

         void ReadTH1FRecord(Record& rec){
          std::cout<<"Reading TH1F Record"<<std::endl;
          ReadTObjectRecord(rec);

          std::cout<<"FNCells: "<<ConvertBuffer<int>(rec.data,8 ) <<std::endl;
          //read axis three times
          short bar_offset = ConvertBuffer<short>(rec.data,10);
          short bar_width = ConvertBuffer<short>(rec.data,12);
          double entries = ConvertBuffer<double>(rec.data,14);
          double norm = ConvertBuffer<double>(rec.data, 18);
          double norm_square = ConvertBuffer<double>(rec.data,22);
          double norm_avg = ConvertBuffer<double>(rec.data,26);
          double norm_avg_square = ConvertBuffer<double>(rec.data, 30);

         }


      public:
         RootFile(const Path& path) : InputFile(path) {
           if(O32_HOST_ORDER == O32_BIG_ENDIAN){
             std::cout<<"Host order aligns with ROOT File Order"<<std::endl;
           }
           else{
             std::cout<<"Host order misalignment with ROOT Standard. Swapping"<<std::endl;
           }

         }

      };
   }
}



#endif //File Guardian
