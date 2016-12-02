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

namespace kvclient {
    class Program {
        static void Main(string[] args) {
            string host = "localhost";
            int port = 9090;
            for (int i = 0; i < args.Length; ++i) {
                if (args[i] == "-server") {
                    string[] str = args[i + 1].Split(':');
                    host = str[0];
                    int.TryParse(str[1], out port);
                }
            }

            try
            {
                var transport = new TSocket("localhost", 9090);
                var protocol = new TBinaryProtocol(transport);
                var client = new KVStore.Client(protocol);

                Result result = new Result();
                for (int i = 0; i < args.Length; ++i)
                {
                    if (args[i] == "-set") result = client.kvset(args[i + 1], args[i + 2]);
                    else if (args[i] == "-get") result = client.kvget(args[i + 1]);
                    else if (args[i] == "-delete") result = client.kvdelete(args[i + 1]);
                }
                Console.WriteLine("\tValue: " + result.Value + "\n\tErrorCode: " + result.Error + "\n\tErrorText" + result.Errortext);

                transport.Open();
            }
            catch (Exception e) { Console.WriteLine(e.ToString()); }
        }
    }
}
