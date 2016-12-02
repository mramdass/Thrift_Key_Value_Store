using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Collections;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;
using Thrift.Server;

namespace kvserver {
    class Program {
        public class ThriftServiceHandler : KVStore.Iface {
            private Dictionary<string, string> kv;

            public Result kvset(string key, string value) {
                Console.WriteLine("\tkvset");
                kv.Add(key, value);
                Result result = new Result();
                result.Value = "";
                result.Error = (ErrorCode)0;
                result.Errortext = "";
                return result;
            }

            public Result kvget(string key) {
                Console.WriteLine("\tkvget");
                Result result = new Result();
                if (kv.ContainsKey(key)) {
                    result.Value = "";
                    result.Error = (ErrorCode)1;
                    result.Errortext = "Key not found";
                }
                else {
                    result.Value = kv[key];
                    result.Error = (ErrorCode)0;
                    result.Errortext = "";
                }
                return result;
            }

            public Result kvdelete(string key) {
                Console.WriteLine("\tkvdelete");
                Result result = new Result();
                if (kv.ContainsKey(key)) {
                    result.Value = "";
                    result.Error = (ErrorCode)1;
                    result.Errortext = "Key not found";
                }
                else {
                    kv.Remove(key);
                    result.Value = "";
                    result.Error = (ErrorCode)0;
                    result.Errortext = "";
                }
                return result;
            }
        }

        static void Main(string[] args) {
            int port = 9090;
            for (int i = 0; i < args.Length; ++i)
                if (args[i] == "-port") int.TryParse(args[i + 1], out port);

            try {
                var handler = new ThriftServiceHandler();
                var processor = new KVStore.Processor(handler);

                TServerTransport transport = new TServerSocket(port);
                TServer server = new TThreadPoolServer(processor, transport);

                Console.WriteLine("Server Start");
                server.Serve();
            }
            catch (Exception e) { Console.WriteLine(e.ToString()); }
        }
    }
}
