//  Libiqnet + Libiqxmlrpc - an object-oriented XML-RPC solution.
//  Copyright (C) 2004 Anton Dedov
//  
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//  
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
//  
//  $Id: http_client.h,v 1.2 2004-05-17 08:43:02 adedov Exp $

#ifndef _libiqxmlrpc_http_client_h_
#define _libiqxmlrpc_http_client_h_

#include "connector.h"
#include "client.h"

namespace iqxmlrpc
{
  class Http_client_connection;
};


//! XML-RPC \b HTTP client's connection (works in blocking mode).
class iqxmlrpc::Http_client_connection: public iqxmlrpc::Client_connection {
  iqnet::Reactor reactor;
  std::string out_str;
  http::Packet* resp_packet;

public:
  Http_client_connection( const iqnet::Socket& );

  void handle_input( bool& );
  void handle_output( bool& );

protected:
  http::Packet* do_process_session( const std::string& );
};


#endif