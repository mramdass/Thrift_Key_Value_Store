//
//  Munieshwar (Kevin) Ramdass
//  Profesor Kurt Harlem
//  CS-GY 9223 H
//  15 October 2016
//
//  KVClient.cpp
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "KVStore.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace kvstore;

int main(int argc, char **argv) {
  string host = "localhost";
  int port = 9090;
  // Argument Parsing
  for (int i = 0; i < argc; ++i) {
    string s = "";
    int c = 0;
	// string copying from pointer without STL methods
    while (argv[i][c]) {
        s += argv[i][c];
        ++c;
    }
	// Testing for equality between strings
	// If argument is -server, get the host and port number
    if (s == "-server") {
      //string hostport = argv[i + 1];
      c = 0;
      s = "";
	  // string copying from pointer
      while (argv[i + 1][c]) {
          s += argv[i + 1][c];
          ++c;
      }
      string str_port = "";
      string hostport = s;
      c = 0;
      host = "";
	  // Getting host/ip up to colon
      while (hostport[c] != ':') {
          host += hostport[c];
          ++c;
      }
      ++c;
	  // Getting port number from colon to NULL
      while (hostport[c] != NULL) {
          str_port += hostport[c];
          ++c;
      }
	  // Assignment the string port value as an int
      port = atoi(str_port.c_str());
    }
  }
  // Setting up Thrift's socket for client
  boost::shared_ptr<TTransport> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  KVStoreClient client(protocol);
  cout << "REQUESTING..." << endl;
  // Create Result object to send and recieve in place of a return
  Result result;

  try {
    transport->open();

    try {
      for (int i = 0; i < argc; ++i) {
        string s = "";
        int c = 0;
		// Getting Function -set, -get, or -delete
		// String copying from pointer
        while (argv[i][c]) {
            s += argv[i][c];
            ++c;
        }
		// Send result to server along with argument string(s) and use modified result from server
        if (s == "-set") {
          client.kvset(result, argv[i + 1], argv[i + 2]);
          if (result.error != (ErrorCode::type)0) {
            cout << "\tError: " << result.error << "\tReason: " << result.errortext << endl;
          }
        }
        else if (s == "-get") {
          client.kvget(result, argv[i + 1]);
          if (result.error != (ErrorCode::type)0) {
            cout << "\tError: " << result.error << "\tReason: " << result.errortext << endl;
          }
          else {
            cout << "\tValue: " << result.value << endl;
          }
        }
        else if (s == "-delete") {
          client.kvdelete(result, argv[i + 1]);
          if (result.error != (ErrorCode::type)0) {
            cout << "\tError: " << result.error << "\tReason: " << result.errortext << endl;
          }
        }
      }

    } catch (exception e) { // Wrong commands sent to server
      result.value = "";
      result.error = (ErrorCode::type)2;
      result.errortext = "Invalid Request";
      cout << "\tError: " << result.error << "\tReason: " << result.errortext << endl;
    }

    transport->close();
  } catch (TException& tx) { // Client failed to establish
    result.value = "";
    result.error = (ErrorCode::type)2;
    result.errortext = tx.what();
    cout << "\tError: " << result.error << "\tReason: " << result.errortext << endl;
  }
}
