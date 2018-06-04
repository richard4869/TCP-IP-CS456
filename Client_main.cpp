#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>



int main ( int argc, char* argv[] )
{
  try
    {
      ClientSocket client_socket ("localhost");

      std::string reply;
      try
	{
        while (true){
//////////////////////////////////////////////////////////////////////////////
              client_socket << "hello";
              client_socket >> reply;
              if(reply == "hello"){
                break;
              }
            }
              client_socket >> reply;
              std::cout<<reply<<std::endl;
              std::cout<<"connection established"<<std::endl;
///////////////////////////////////////////////////////////////////////////////
        std::cout<<"input the command you want"<<std::endl;
        std::string command,argu,contents;
        while (std::cin >>command){
            if(command == "put"){
                std::cin >> argu;
                command = command + " " + argu;                     //put a file
                client_socket << command;
                std::cout << "input the content"<<std::endl;
                std::cin>>contents;
                client_socket << contents;
            }else if(command == "get"){
                std::cin >> argu;
                command = command + " " + argu;                     //get a file
                client_socket << command;
                std::cout<<"getting the content";
                    client_socket >> contents;
                    std::cout << contents<<std::endl;
                 std::cout <<std::endl;
            }else if(command == "close"){
                client_socket << command;
                break;
            }
        }
	}
      catch ( SocketException& ) {}

      //std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
