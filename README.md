# Thrift_Key_Value_Store
C++ Server  
C++ Client  
C# Server  
C# Client  
Consistency Test Client  

### Running  
Alternatively, on Windows you may enter kvserver.exe and kvclient.exe
```
./kvserver -port <number>
./kvclient -server <ip>:<number> -set <string> <string>
./kvclient -server <ip>:<number> -get <string>
./kvclient -server <ip>:<number> -delete <string>
./consistency_test -server <ip>:<port>
```
```
./kvserver -port 9090
./kvclient -server localhost:9090 -set "Key" "Value"
./kvclient -server localhost:9090 -get "Key"
./kvclient -server localhost:9090 -delete "Key"
./consistency_test -server localhost:9090
```

### Installing Thrift
Following the instructions below. Installation on Ubuntu 16.04 for common languages is easy as well as on Visual Studio 2015 for C#.  
<https://thrift.apache.org/docs/install/>

### Generating Language Specific Includes
```
thrift -gen-cpp kvstore.thrift
thrift -gen-csharp kvstore.thrift
thrift -gen-java kvstore.thrift
thrift -gen-py kvstore.thrift
thrift -gen-c kvstore.thrift
```

### C++ Compile Command (Ubuntu 16.04)
```
g++ -std=c++11 -o <NAME> -I./gen-cpp -I/usr/local/include/thrift/ <NAME>.cpp gen-cpp/kvstore_constants.cpp gen-cpp/KVStore.cpp gen-cpp/kvstore_types.cpp -L/usr/local/lib -lthrift -lpthread
```


### C# Build
Use Visual Studio 2015 for easy build and run in C#.
