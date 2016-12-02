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
```
```
./kvserver -port 9090
./kvclient -server localhost:9090 -set "Key" "Value"
./kvclient -server localhost:9090 -get "Key"
./kvclient -server localhost:9090 -delete "Key"
```
