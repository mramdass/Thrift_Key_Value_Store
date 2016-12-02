//
//  Munieshwar (Kevin) Ramdass
//  Profesor Kurt Harlem
//  CS-GY 9223 H
//  15 October 2016
//
//  KVServer.cpp
//

#include "kvstore_types.h"
#include "KVStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::kvstore;

class KVStoreHandler : virtual public KVStoreIf {
 public:
  KVStoreHandler() {}
  // _return is the object the client will use to view value and errors
  // _return functions as this method "return" call
  // Strings key and value is used to insert into an STL map, kvmap
  void kvset(Result& _return, const std::string& key, const std::string& value) {
    // Your implementation goes here
    printf("kvset\n");
    kvmap[key] = value;
    _return.value = "";
    _return.error = (ErrorCode::type)0;
    _return.errortext = "";
  }
  // _return is the object the client will use to view value and errors
  // _return functions as this method "return" call
  // Strings key is used to find from an STL map, kvmap
  void kvget(Result& _return, const std::string& key) {
    // Your implementation goes here
    printf("kvget\n");
    if (kvmap.find(key) == kvmap.end()) {
      _return.value = "";
      _return.error = (ErrorCode::type)1;
      _return.errortext = "Key not found";
    }
    else {
      _return.value = kvmap[key];
      _return.error = (ErrorCode::type)0;
      _return.errortext = "";
    }
  }
  // _return is the object the client will use to view value and errors
  // _return functions as this method "return" call
  // Strings key is used to delete from an STL map, kvmap
  void kvdelete(Result& _return, const std::string& key) {
    // Your implementation goes here
    printf("kvdelete\n");
    if (kvmap.find(key) == kvmap.end()) {
      _return.value = "";
      _return.error = (ErrorCode::type)1;
      _return.errortext = "Key not found";
    }
    else {
      kvmap.erase(key);
      _return.value = "";
      _return.error = (ErrorCode::type)0;
      _return.errortext = "";
    }
  }
 private:
  // STL data structure map (hashmap) used for quick inserts and accessing
  std::map<std::string, std::string> kvmap;

};

int main(int argc, char **argv) {
  int port = 9090;

    for (int i = 0; i < argc; ++i) {
      std::string s = "";
      int c = 0;
	  // Copying string from pointer to later test for string equality
      while (argv[i][c]) {
          s += argv[i][c];
          ++c;
      }
	  // Test for argument string equality if -port is given
      if (s == "-port") {
        port = atoi(argv[i + 1]);
      }
    }
  // Setting up Trift's server handler using boost shared pointers
  shared_ptr<KVStoreHandler> handler(new KVStoreHandler());
  shared_ptr<TProcessor> processor(new KVStoreProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  std::cout << "SERVER INITIATE" << std::endl;
  server.serve();
  // Server should not get to this point
  // Server has stopped functioning if the following output is displayed
  std::cout << "SERVER INTERRUPT" << std::endl;
  return 0;
}

