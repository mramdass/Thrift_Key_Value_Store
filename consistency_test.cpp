//
//  Munieshwar (Kevin) Ramdass
//  Profesor Kurt R.
//  CS-GY 9223 H
//  23 November 2016
//
//  KVClient.cpp
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <fstream>
#include <thread>
#include <mutex>
#include <map>
//#include <unordered_map>
//#include <future>
//#include <tuple>
//#include <ctime>
//#include <stack>
//#include <queue>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "KVStore.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace kvstore;

// Used to connect to server
string host("localhost");
int port(9090);

// Key and values to use with requests
string key = "*";
vector<string> strings;

// Sequence to request and request to sequence log maps
map<int, string> MLOG;
map<string, int> RLOG;

// Logs all possible regular get values at each sequence
map<int, vector<string>> possible_gets;

// Sequence number to log respective request
int SEQ(0);
mutex mtx;

// Just used to make debugging output easier - 7 chars per value
int VALUE_SIZE(7);

// Output Data Structures - Used for debugging reasons
void write_logs() {
    cout << "\tWriting Logs..." << endl;
    ofstream mfs("mlog.txt");
    for (auto k : MLOG) mfs << k.first << ": " << k.second << endl;
    mfs.close();
    ofstream rfs("rlog.txt");
    for (auto k : RLOG) rfs << k.first << ": " << k.second << endl;
    rfs.close();
}

// Fill words with same length unique strings along with a marker
void fill_words(vector<string>& values) {
    for (int i(0); i < 50; ++i) {
        string temp(to_string(i));
        while (temp.length() < VALUE_SIZE) temp += '^';
        values.push_back(temp);
    }
}

// Client will spam kvset requests from strings vector
void setter(int s, int e) {
    for (int i(s); i < e; ++i) {
        boost::shared_ptr<TTransport> socket(new TSocket(host, port));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KVStoreClient client(protocol);
        Result result;
        try {
            transport->open();
            //for (int i(s); i < e; ++i) {
            try {
                mtx.lock();
                int SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                RLOG["START-SET " + strings[i]] = SEQ_;
                MLOG[SEQ_] = "START-SET " + strings[i];
                mtx.unlock();

                client.kvset(result, key, strings[i]);

                mtx.lock();
                SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                RLOG["FINISH-SET " + strings[i]] = SEQ_;
                MLOG[SEQ_] = "FINISH-SET " + strings[i];
                mtx.unlock();
            }
            catch (exception e) {
                cout << "ERROR: " << e.what() << endl;
                exit(2);
            }
            transport->close();
        }
        catch (TException& tx) {
            cout << "ERROR: " << tx.what() << endl;
            exit(2);
        }
    }
    cout << "\tSet Client Finished..." << endl;
}

// Differ from setter in that this function makes only one connection
void setter_(int s, int e) {
    //for (int i(s); i < e; ++i) {
    boost::shared_ptr<TTransport> socket(new TSocket(host, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KVStoreClient client(protocol);
    Result result;
    try {
        transport->open();
        for (int i(s); i < e; ++i) {
            try {
                mtx.lock();
                int SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                RLOG["START-SET " + strings[i]] = SEQ_;
                MLOG[SEQ_] = "START-SET " + strings[i];
                mtx.unlock();

                client.kvset(result, key, strings[i]);

                mtx.lock();
                SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                RLOG["FINISH-SET " + strings[i]] = SEQ_;
                MLOG[SEQ_] = "FINISH-SET " + strings[i];
                mtx.unlock();
            }
            catch (exception e) {
                cout << "ERROR: " << e.what() << endl;
                exit(2);
            }
        }
        transport->close();
    }
    catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
        exit(2);
    }
    //}
    cout << "\tSet Client Finished..." << endl;
}

// Client will spam 'stop'-number of kvget requests
void getter(int stop) {
    int start = 0;
    while (start < stop) {
        boost::shared_ptr<TTransport> socket(new TSocket(host, port));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KVStoreClient client(protocol);
        Result result;
        try {
            transport->open();
            //while (start < stop) {

            try {
                ++start;

                mtx.lock();
                int SEQ_ = ++SEQ;
                mtx.unlock();

                int marker = SEQ_; // Save a copy of the sequence number when value is received

                client.kvget(result, key);

                mtx.lock();
                SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                if (result.error == (ErrorCode::type)0) {
                    RLOG[to_string(marker) + " FINISH-GET " + result.value] = SEQ_;
                    MLOG[SEQ_] = to_string(marker) + " FINISH-GET " + result.value;

                    RLOG[to_string(SEQ_) + " START-GET " + result.value] = marker;
                    MLOG[marker] = to_string(SEQ_) + " START-GET " + result.value;
                }
                else {
                    RLOG[to_string(marker) + " FINISH-GET ERROR " + to_string(SEQ_) + " " + to_string(marker)] = SEQ_;
                    MLOG[SEQ_] = to_string(marker) + " FINISH-GET ERROR " + to_string(SEQ_) + " " + to_string(marker);

                    RLOG["START-GET ERROR " + to_string(marker) + " " + to_string(SEQ_)] = marker;
                    MLOG[marker] = "START-GET ERROR " + to_string(marker) + " " + to_string(SEQ_);
                }
                mtx.unlock();
            }
            catch (exception e) {
              cout << "ERROR: " << e.what() << endl;
              exit(2);
            }
            transport->close();
        }
        catch (TException& tx) {
            cout << "ERROR: " << tx.what() << endl;
            exit(2);
        }
    }
    cout << "\tGet Client Finished..." << endl;
}

// Differ from getter in that this function makes only one connection
void getter_(int stop) {
    int start = 0;
    //while (start < stop) {
    boost::shared_ptr<TTransport> socket(new TSocket(host, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KVStoreClient client(protocol);
    Result result;
    try {
        transport->open();
        while (start < stop) {

            try {
                ++start;

                mtx.lock();
                int SEQ_ = ++SEQ;
                mtx.unlock();

                int marker = SEQ_; // Save a copy of the sequence number when value is received

                client.kvget(result, key);

                mtx.lock();
                SEQ_ = ++SEQ;
                mtx.unlock();

                mtx.lock();
                if (result.error == (ErrorCode::type)0) {
                    RLOG[to_string(marker) + " FINISH-GET " + result.value] = SEQ_;
                    MLOG[SEQ_] = to_string(marker) + " FINISH-GET " + result.value;

                    RLOG[to_string(SEQ_) + " START-GET " + result.value] = marker;
                    MLOG[marker] = to_string(SEQ_) + " START-GET " + result.value;
                }
                else {
                    RLOG[to_string(marker) + " FINISH-GET ERROR " + to_string(SEQ_) + " " + to_string(marker)] = SEQ_;
                    MLOG[SEQ_] = to_string(marker) + " FINISH-GET ERROR " + to_string(SEQ_) + " " + to_string(marker);

                    RLOG["START-GET ERROR " + to_string(marker) + " " + to_string(SEQ_)] = marker;
                    MLOG[marker] = "START-GET ERROR " + to_string(marker) + " " + to_string(SEQ_);
                }
                mtx.unlock();
            }
            catch (exception e) {
                cout << "ERROR: " << e.what() << endl;
                exit(2);
            }
        }
        transport->close();
    }
    catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
        exit(2);
    }
    //}
    cout << "\tGet Client Finished..." << endl;
}

// Used to flush the server's key that the setter and getter will use later
void flush_key() {
    boost::shared_ptr<TTransport> socket(new TSocket(host, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KVStoreClient client(protocol);
    Result result;
    try {
        transport->open();
        try {
            client.kvdelete(result, key);
        }
        catch (exception e) {
          cout << "ERROR: " << e.what() << endl;
          exit(2);
        }
        transport->close();
    }
    catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
        exit(2);
    }
    cout << "\tDelete Client Flushed Key..." << endl;
}

// Changes a sub-string to a different string
void replace(string& str, const string& from, const string& to) {
    size_t start = str.find(from);
    if (start == string::npos) return;
    str.replace(start, from.length(), to);
}

// Removes the sequence number in the beginning of get requests
// Example: 10 FINISH-GET [value] <-- returns "FINISH-GET [value]"
string remove_1(string str) {
    return str.substr(str.find_first_of(" \t") + 1);
}

// Return the sequence number in the beginning of get requests
// Example: 10 FINISH-GET [value] <-- returns "10"
string take_1(string str) {
    return str.substr(0, str.find(' '));
}

// Returns the value of a request
// Example: FINISH-SET [value] <-- returns "[value]"
string strip_value(string str) {
    string temp = "";
    for (int i(str.length() - VALUE_SIZE); i < str.length(); ++i)
        temp += str[i];
    return temp;
}

// Uses a stack-like technique to obtain all possible regular get values per sequence number
void fill_possible_gets() {
    map<string, bool> s;  // Used like a stack to filter all concurrent set requests; bool is useless
    int prev = -1;

    for (int k(1); k <= SEQ; ++k) {
    //for (auto k : MLOG) {
        if (s.count(MLOG[k]) == 0 && MLOG[k].find("START-SET") != string::npos) {
            s[MLOG[k]] = true;
        }
        else if (MLOG[k].find("FINISH-SET") != string::npos) {
            if (prev != -1) {
                string temp = MLOG[prev];
                replace(temp, "FINISH-SET", "START-SET");
                s.erase(temp);
            }
            prev = k;
        }
        vector<string> possible;
        possible_gets[k] = possible;
        for (auto v : s) possible_gets[k].push_back(strip_value(v.first));
    }
}

// Alters possible_gets by stripping get values that are atomically impossible as sequence increases
void filter_possible_gets() {
    for (auto k : possible_gets) {

        // Determine with set requests has been committed based on get requests
        if (MLOG[k.first].find("FINISH-GET") != string::npos) {
            int start_seq = atoi(take_1(MLOG[k.first]).c_str());
            string val = strip_value(MLOG[k.first]);
            vector<string> prev_vals;
            for (int i(1); i <= start_seq; ++i) {
                for (int j(0); j < possible_gets[i].size(); ++j) {
                    int finish_set = RLOG["FINISH-SET " + possible_gets[i][j]];
                    //if (!(finish_set < k.first && start_seq < finish_set))
                    if (start_seq > finish_set)
                        prev_vals.push_back(possible_gets[i][j]);
                }
            }

            // Make sure all values are unique; remove the get value as it is current
            prev_vals.erase(remove(prev_vals.begin(), prev_vals.end(), val), prev_vals.end());
            sort(prev_vals.begin(), prev_vals.end() );
            prev_vals.erase(unique(prev_vals.begin(), prev_vals.end()), prev_vals.end());

            // For every value after this FINISH-GET, filter out all the old values (prev_vals)
            try {
                for (int l(k.first + 1); l <= SEQ; ++l) {
                    for (int i(0); i < prev_vals.size(); ++i) {
                        for (int j(0); j < possible_gets[l].size(); j) {
                            if (prev_vals[i] == possible_gets[l][j] && k.first > RLOG["FINISH-SET " + prev_vals[i]])
                                possible_gets[l].erase(remove(possible_gets[l].begin(), possible_gets[l].end(), prev_vals[i]), possible_gets[l].end());
                            else ++j;
                        }
                    }
                }
            }
            catch (exception e) { cout << "Met end of possible_gets" << endl; } // Should never run
        }
    }
}

// Removes concurrent get requests; checks if last set value is reflected in current get value
// This check is not necessary since safety is merely a subset of regularity and atomicity
bool safety() {
    map<string, int> ss;  // Will eventually have all the non-concurrent gets
    map<string, bool> s;  // Used like a stack to filter all concurrent get requests
    int prev_seq(-1);
    bool can_get(false);

    // Relies on the fact that C++ sorts sequence numbers (keys)
    for (int k(1); k <= SEQ; ++k) {
    //for (auto k : MLOG) {
        if (s.count(MLOG[k]) == 0 && MLOG[k].find("START-SET") != string::npos) {
            s[MLOG[k]] = true;
            can_get = false;
        }
        else if (MLOG[k].find("FINISH-SET") != string::npos) {
            string temp = MLOG[k];
            replace(temp, "FINISH-SET", "START-SET");
            s.erase(temp);
            can_get = false;
            //ss[k.second] = k.first;
        }

        // Will force a START-GET followed immediately by a FINISH-GET
        else if (MLOG[k].find("START-GET") != string::npos && MLOG[k].find("ERROR") == string::npos && s.empty()) {
            prev_seq = k;
            can_get = true;
        }
        else if (MLOG[k].find("FINISH-GET") != string::npos && MLOG[k].find("ERROR") == string::npos && can_get && s.empty() && prev_seq == stoi(take_1(MLOG[k]).c_str())) {
            can_get = false;
            ss[MLOG[k]] = k;
        }
    }

    // Check if value's get request occurs after value's set request
    for (auto k : ss) {
        if (k.first.find("FINISH-GET") != string::npos) {
            int start_seq = stoi(take_1(k.first).c_str());

            // Find the associating set finish sequence number
            string temp = remove_1(k.first);
            replace(temp, "-GET", "-SET");
            int finish_set = RLOG[temp];

            // get of a value cannot happen after set of a value
            if (finish_set > k.second) return false;

            // Checking that last set is reflected in current get; check for start sets after value set
            for (int i(finish_set + 1); i < k.second; ++i)
                if (MLOG[i].find("START-SET") != string::npos)
                    return false;
        }
    }
    return true;
}

// Checks each sequence number and all possible values from possible_gets against FINISH-GET values in MLOG
bool check_gets() {
    int expect = 0;
    int got = 0;
    for (auto k : MLOG) {
        if (k.second.find("FINISH-GET") != string::npos && k.second.find("ERROR") == string::npos) {
            ++expect;
            for (int i(stoi(take_1(k.second))); i <= k.first; ++i) {
                if (find(possible_gets[i].begin(), possible_gets[i].end(), strip_value(k.second)) != possible_gets[i].end()) {
                    ++got;
                    break;
                }
            }
        }
    }
    return expect == got;
}

// fill_possible_gets() is necessary
// Checking for regularity is not necessary
bool regularity() {
    fill_possible_gets();
    return check_gets();
}

// This function determines consistency
bool atomicity() {
    filter_possible_gets();
    return check_gets();
}

bool run_tests() {
    cout << "\tRunning Consistency Tests..." << endl;
    possible_gets = {};
    if (safety()) cout << "\tSystem is safe" << endl;
    if (regularity()) cout << "\tSystem is regular" << endl;
    if (atomicity()) {
        cout << "\tSystem is atomic" << endl;
        cout << "\tSYSTEM IS CONSISTENT" << endl;
        return true;
    }
    cout << "\tSYSTEM IS NOT CONSISTENT" << endl;
    return false;
}

bool validate_log() {
    if (SEQ != MLOG.size() || SEQ != RLOG.size() || MLOG.size() != RLOG.size()) {
        cout << "Re-running this test is advised. Mismatched number of requests perhaps because of a repeated value." << endl;
        exit(1);
    }
    bool val_set = false;
    bool val_seq = strings.size() * 12 + 1;
    for (int i(1); i <= SEQ; ++i) {
        if (MLOG[i].find("FINISH-SET") != string::npos) {val_set = true; val_seq = i;}

        // In rare cases, C++ maps insert values do not appear
        if (MLOG.count(i) == 0) {
            cout << "Re-running this test is advised. Log shows corruption. A sequence is not reflected." << endl;
            return false;
        }
        if (RLOG.count(MLOG[i]) == 0) {
            cout << "Re-running this test is advised. Log shows corruption. A request is not reflected." << endl;
            return false;
        }

        // Check if KVStore has set the key, but gets return ERROR - Allows ERROR for only the first get request
        if (MLOG[i].find("FINISH-GET") != string::npos && MLOG[i].find("ERROR") != string::npos && val_set) {
            if (stoi(take_1(MLOG[i]).c_str()) > val_seq) {
                cout << "Re-running this test is advised. Log shows corruption. Get ERROR after set." << endl;
                return false;
            }
        }

        // Check for magic gets that show a value not set in the first place
        if (MLOG[i].find("FINISH-GET") != string::npos && MLOG[i].find("ERROR") == string::npos) {
            string temp = remove_1(MLOG[i]);
            replace(temp, "-GET", "-SET");
            if (RLOG.count(temp) == 0) {
                cout << "Encountered a value that consistency_test did not input (perhaps as yet)." << endl;
                exit(1);
            }
        }
    }
    return true;
}

void spam_requests(int orig_size) {
    try {
        flush_key();
        std::thread s0(setter_, 0, orig_size);
        std::thread s1(setter, orig_size, orig_size * 2);
        std::thread s2(setter, orig_size * 2, strings.size());
        std::thread g0(getter, orig_size * 2);
        std::thread g1(getter_, orig_size);

        s0.join();
        s1.join();
        s2.join();
        g0.join();
        g1.join();
    }
    catch (exception e) { cout << e.what() << endl; exit(2); }
}

//  ________________MANUAL TEST CASES _____________________

void case_a() {
    MLOG = {}; RLOG = {};
    MLOG[1] = "8 START-GET AAAAAAA";
    MLOG[2] = "START-SET AAAAAAA";
    MLOG[3] = "6 START-GET AAAAAAA";
    MLOG[4] = "FINISH-SET AAAAAAA";
    MLOG[5] = "START-SET BBBBBBB";
    MLOG[6] = "3 FINISH-GET AAAAAAA";
    MLOG[7] = "FINISH-SET BBBBBBB";
    MLOG[8] = "1 FINISH-GET AAAAAAA";
    SEQ = 8;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void case_b() {
    MLOG = {}; RLOG = {};
    MLOG[1] = "8 START-GET BBBBBBB";
    MLOG[2] = "START-SET AAAAAAA";
    MLOG[3] = "6 START-GET BBBBBBB";
    MLOG[4] = "FINISH-SET AAAAAAA";
    MLOG[5] = "START-SET BBBBBBB";
    MLOG[6] = "3 FINISH-GET BBBBBBB";
    MLOG[7] = "FINISH-SET BBBBBBB";
    MLOG[8] = "1 FINISH-GET BBBBBBB";
    SEQ = 8;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void case_c() {
    MLOG = {}; RLOG = {};
    MLOG[1] = "START-SET AAAAAAA";
    MLOG[2] = "START-SET BBBBBBB";
    MLOG[3] = "6 START-GET BBBBBBB";
    MLOG[4] = "FINISH-SET AAAAAAA";
    MLOG[5] = "START-SET CCCCCCC";
    MLOG[6] = "3 FINISH-GET BBBBBBB";
    MLOG[7] = "9 START-GET AAAAAAA";
    MLOG[8] = "FINISH-SET CCCCCCC";
    MLOG[9] = "7 FINISH-GET AAAAAAA";
    MLOG[10] = "FINISH-SET BBBBBBB";
    SEQ = 10;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void case_d() {
    MLOG = {}; RLOG = {};
    MLOG[1] = "START-SET AAAAAAA";
    MLOG[2] = "START-SET BBBBBBB";
    MLOG[3] = "5 START-GET BBBBBBB";
    MLOG[4] = "FINISH-SET AAAAAAA";
    MLOG[5] = "3 FINISH-GET BBBBBBB";
    MLOG[6] = "7 START-GET AAAAAAA";
    MLOG[7] = "6 FINISH-GET AAAAAAA";
    MLOG[8] = "FINISH-SET BBBBBBB";
    SEQ = 8;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void case_e() { // ERROR CASE
    MLOG = {}; RLOG = {};
    MLOG[1] = "START-SET AAAAAAA";
    MLOG[2] = "START-SET BBBBBBB";
    MLOG[3] = "6 START-GET BBBBBBB";
    MLOG[4] = "FINISH-SET AAAAAAA";
    MLOG[5] = "START-SET CCCCCCC";
    MLOG[6] = "3 FINISH-GET BBBBBBB";
    MLOG[7] = "9 START-GET AAAAAAA";
    MLOG[8] = "FINISH-SET CCCCCCC";
    MLOG[9] = "7 FINISH-GET AAAAAAA";
    MLOG[10] = "FINISH-SET BBBBBBB";
    MLOG[11] = "12 START-GET VVVVVVV";
    MLOG[12] = "11 FINISH-GET VVVVVVV";
    SEQ = 12;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void case_f() { // ERROR CASE - FROM HP PAPER - Regular, but not Atomic
    MLOG = {}; RLOG = {};
    MLOG[1] = "START-SET AAAAAAA";
    MLOG[2] = "FINISH-SET AAAAAAA";
    MLOG[3] = "START-SET BBBBBBB";
    MLOG[4] = "5 START-GET BBBBBBB";
    MLOG[5] = "4 FINISH-GET BBBBBBB";
    MLOG[6] = "7 START-GET AAAAAAA";
    MLOG[7] = "6 FINISH-GET AAAAAAA";
    MLOG[8] = "FINISH-SET BBBBBBB";
    SEQ = 8;
    for (auto l : MLOG) {RLOG[l.second] = l.first;}
    run_tests();
}

void run_test_cases() {
    cout << "Case a" << endl; case_a();
    cout << "Case b" << endl; case_b();
    cout << "Case c" << endl; case_c();
    cout << "Case d" << endl; case_d();
    cout << "Case e" << endl; case_e(); // Not consistent - Not safe
    cout << "Case f" << endl; case_f(); // Not consistent - FROM HP PAPER - Regular, but not Atomic
    write_logs();
}

// ________________________________________________________

int main(int argc, char **argv) {
    // Process arguments character by character
    for (int i = 0; i < argc; ++i) {
        string s = "";
        int c = 0;
        while (argv[i][c]) {
            s += argv[i][c];
            ++c;
        }
        if (s == "-server") {
            //string hostport = argv[i + 1];
            c = 0;
            s = "";
            while (argv[i + 1][c]) {
                s += argv[i + 1][c];
                ++c;
            }
            string str_port = "";
            string hostport = s;
            c = 0;
            host = "";
            while (hostport[c] != ':') {
                host += hostport[c];
                ++c;
            }
            ++c;
            while (hostport[c] != NULL) {
                str_port += hostport[c];
                ++c;
            }
            port = atoi(str_port.c_str());
        }
    }

    // Fill strings with three sets of markers that each of the 3 setters will use in their thread
    // Markers are used mainly for debugging purposes; SEQ could have been used as set values
    fill_words(strings);
    int orig_size(strings.size());
    for (int s(0); s < orig_size; ++s) {
        string temp(strings[s]);
        std::replace(temp.begin(), temp.end(), '^', '<');
        strings.push_back(temp);
    }
    for (int s(0); s < orig_size; ++s) {
        string temp(strings[s]);
        std::replace(temp.begin(), temp.end(), '^', '>');
        strings.push_back(temp);
    }

    // Sending multiple get and set requests
    spam_requests(orig_size);

    // Run a log validate function to check for exit(2) conditions like ERROR response
    if (!validate_log()) {
        cout << "Captured log is not valid. Cannot run consistency tests." << endl;
        write_logs();
        exit(2);
    }

    if (run_tests())
        exit(0); // Exit 0 to indicate successful client termination and consistent server
    exit(1); // Exit 1 to indicate inconsistent server

    run_test_cases(); // Testing line if the above exit statements are commented out
}
