#include <memory>
#include <libxml++/libxml++.h>
#include <libiqxmlrpc/null_transport.h>
#include <libiqxmlrpc/method.h>

using namespace iqxmlrpc;


Server::Server( Method_dispatcher* d ):
  disp(d),
  request(0),
  resp_value(0)
{
}


Server::~Server()
{
  delete request;
}


Response Server::execute( const std::string& request_string )
{
  std::string error_msg;
  int fault_code;
  
  try {
    parse_request( request_string );
    execute();
    return Response( resp_value );
  }
  catch( const xmlpp::exception& e )
  {
    error_msg  = e.what();
    fault_code = Fault_code::xml_parser;
  }
  catch( const Exception& e )
  {
    error_msg = e.what();
    fault_code = e.code();
  }

  return Response( fault_code, error_msg );
}


void Server::parse_request( const std::string& request_string )
{
  xmlpp::DomParser parser;
  parser.set_substitute_entities();
  parser.parse_memory( request_string );

  delete request;
  request = 0;
  request = new Request( parser.get_document() );
}


void Server::execute()
{
  std::auto_ptr<Method> m( disp->create_method(request->get_name()) );
  m->execute( request->get_params(), resp_value );
}


// --------------------------------------------------------------------------
Response Client::execute( const std::string& name, const Param_list& pl )
{
  try 
  {
    std::string resp_str = do_execute( Request( name, pl ) );
  
    xmlpp::DomParser parser;
    parser.set_substitute_entities();
    parser.parse_memory( resp_str );
  
    return Response( parser.get_document() );
  }
  catch( const xmlpp::exception& e )
  {
    throw Parse_error::caused( e.what() );
  }
}
