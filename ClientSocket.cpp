// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <string>

ClientSocket::ClientSocket (std::string host)
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }
    std::cout<<"input:connect + port number to connect to the server"<<std::endl;
    std::string s,ns;
    std::cin >> s;
    std::cin >> ns;
    std::stringstream ss(ns);
    int portnum;
    if(s == "connect"){
      ss >> portnum;
      std::cout<<portnum<<std::endl;
      if ( ! Socket::connect (host, portnum) )
        {
        throw SocketException ( "Could not bind to port." );
        }
    }
}


const ClientSocket& ClientSocket::operator << ( const std::string& sa ) const
{
  if ( ! Socket::send ( sa ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& sa ) const
{
  if ( ! Socket::recv ( sa ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}
