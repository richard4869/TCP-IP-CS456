#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>
#include <sstream>

int main ( int argc, char* argv[] )
{
  std::cout << "running....\n";

  try
    {
      // Create the socket with random port number
      int portnum = rand()%20000 + 200;
      ServerSocket server (portnum);
      std::cout << "port number: "<<portnum<<"\n";
    while(true){
	  ServerSocket new_sock;
	  server.accept ( new_sock );
	  try
	    {
////////////////////////////////////////////////////////////////////////////////
        while (true){
		  std::string data;            //accept hello
		  new_sock >> data;
		  if(data=="hello"){
		  new_sock << "hello";
		  break;
		  }else{
		  new_sock << "resend";        //resend
		  }
        }
////////////////////////////////////////////////////////////////////////////////
        std::string sdir;
        DIR* dir;
        struct dirent *ent;
        if ((dir = opendir (".//Files")) != NULL) {
            /* get all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            sdir = sdir + ent->d_name+" ";
            }
        new_sock << sdir;
        closedir(dir);
        } else {
            /* could not open directory */
            throw SocketException ( "Could not open directory." );
            }
/////////////////////////////////////////////////////////////////////////////////
        std::string data,first,second,contents;
        while(true){
            new_sock >> data;
            std::stringstream ss(data);
            ss >> first;
            if(first == "put"){
                ss >> second;                     //put a file
                new_sock << "Okey";
                std::ofstream myfile;
                std::string pwd = ".//Files//"+second;
                myfile.open(pwd.c_str());
                new_sock >> contents;
                myfile << contents;
                myfile.close();
            }else if(first == "get"){               //get a file
                ss >> second;
                std::ifstream file;
                std::string contents;
                std::string pwd = "Files/"+second;
                std::cout<<pwd<<std::endl;
                file.open(pwd.c_str());
                if(file.is_open()){
                    std::cout<<"sending the file"<<std::endl;
                    std::string line;
                    while(! file.eof() ){
                        getline(file,line);
                        contents = contents + line;
                    }
                    file.close();
                    new_sock << contents;
                }else{
                new_sock << "no such file";
                new_sock << "end";
                }
            }else if(first == "close"){
                break;
            }
        }
	    }
	  catch ( SocketException& ) {}
	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}
