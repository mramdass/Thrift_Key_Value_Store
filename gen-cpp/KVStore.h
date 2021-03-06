/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef KVStore_H
#define KVStore_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "kvstore_types.h"

namespace kvstore {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class KVStoreIf {
 public:
  virtual ~KVStoreIf() {}
  virtual void kvset(Result& _return, const std::string& key, const std::string& value) = 0;
  virtual void kvget(Result& _return, const std::string& key) = 0;
  virtual void kvdelete(Result& _return, const std::string& key) = 0;
};

class KVStoreIfFactory {
 public:
  typedef KVStoreIf Handler;

  virtual ~KVStoreIfFactory() {}

  virtual KVStoreIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(KVStoreIf* /* handler */) = 0;
};

class KVStoreIfSingletonFactory : virtual public KVStoreIfFactory {
 public:
  KVStoreIfSingletonFactory(const boost::shared_ptr<KVStoreIf>& iface) : iface_(iface) {}
  virtual ~KVStoreIfSingletonFactory() {}

  virtual KVStoreIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(KVStoreIf* /* handler */) {}

 protected:
  boost::shared_ptr<KVStoreIf> iface_;
};

class KVStoreNull : virtual public KVStoreIf {
 public:
  virtual ~KVStoreNull() {}
  void kvset(Result& /* _return */, const std::string& /* key */, const std::string& /* value */) {
    return;
  }
  void kvget(Result& /* _return */, const std::string& /* key */) {
    return;
  }
  void kvdelete(Result& /* _return */, const std::string& /* key */) {
    return;
  }
};

typedef struct _KVStore_kvset_args__isset {
  _KVStore_kvset_args__isset() : key(false), value(false) {}
  bool key :1;
  bool value :1;
} _KVStore_kvset_args__isset;

class KVStore_kvset_args {
 public:

  KVStore_kvset_args(const KVStore_kvset_args&);
  KVStore_kvset_args& operator=(const KVStore_kvset_args&);
  KVStore_kvset_args() : key(), value() {
  }

  virtual ~KVStore_kvset_args() throw();
  std::string key;
  std::string value;

  _KVStore_kvset_args__isset __isset;

  void __set_key(const std::string& val);

  void __set_value(const std::string& val);

  bool operator == (const KVStore_kvset_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvset_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvset_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KVStore_kvset_pargs {
 public:


  virtual ~KVStore_kvset_pargs() throw();
  const std::string* key;
  const std::string* value;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvset_result__isset {
  _KVStore_kvset_result__isset() : success(false) {}
  bool success :1;
} _KVStore_kvset_result__isset;

class KVStore_kvset_result {
 public:

  KVStore_kvset_result(const KVStore_kvset_result&);
  KVStore_kvset_result& operator=(const KVStore_kvset_result&);
  KVStore_kvset_result() {
  }

  virtual ~KVStore_kvset_result() throw();
  Result success;

  _KVStore_kvset_result__isset __isset;

  void __set_success(const Result& val);

  bool operator == (const KVStore_kvset_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvset_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvset_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvset_presult__isset {
  _KVStore_kvset_presult__isset() : success(false) {}
  bool success :1;
} _KVStore_kvset_presult__isset;

class KVStore_kvset_presult {
 public:


  virtual ~KVStore_kvset_presult() throw();
  Result* success;

  _KVStore_kvset_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KVStore_kvget_args__isset {
  _KVStore_kvget_args__isset() : key(false) {}
  bool key :1;
} _KVStore_kvget_args__isset;

class KVStore_kvget_args {
 public:

  KVStore_kvget_args(const KVStore_kvget_args&);
  KVStore_kvget_args& operator=(const KVStore_kvget_args&);
  KVStore_kvget_args() : key() {
  }

  virtual ~KVStore_kvget_args() throw();
  std::string key;

  _KVStore_kvget_args__isset __isset;

  void __set_key(const std::string& val);

  bool operator == (const KVStore_kvget_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvget_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvget_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KVStore_kvget_pargs {
 public:


  virtual ~KVStore_kvget_pargs() throw();
  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvget_result__isset {
  _KVStore_kvget_result__isset() : success(false) {}
  bool success :1;
} _KVStore_kvget_result__isset;

class KVStore_kvget_result {
 public:

  KVStore_kvget_result(const KVStore_kvget_result&);
  KVStore_kvget_result& operator=(const KVStore_kvget_result&);
  KVStore_kvget_result() {
  }

  virtual ~KVStore_kvget_result() throw();
  Result success;

  _KVStore_kvget_result__isset __isset;

  void __set_success(const Result& val);

  bool operator == (const KVStore_kvget_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvget_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvget_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvget_presult__isset {
  _KVStore_kvget_presult__isset() : success(false) {}
  bool success :1;
} _KVStore_kvget_presult__isset;

class KVStore_kvget_presult {
 public:


  virtual ~KVStore_kvget_presult() throw();
  Result* success;

  _KVStore_kvget_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KVStore_kvdelete_args__isset {
  _KVStore_kvdelete_args__isset() : key(false) {}
  bool key :1;
} _KVStore_kvdelete_args__isset;

class KVStore_kvdelete_args {
 public:

  KVStore_kvdelete_args(const KVStore_kvdelete_args&);
  KVStore_kvdelete_args& operator=(const KVStore_kvdelete_args&);
  KVStore_kvdelete_args() : key() {
  }

  virtual ~KVStore_kvdelete_args() throw();
  std::string key;

  _KVStore_kvdelete_args__isset __isset;

  void __set_key(const std::string& val);

  bool operator == (const KVStore_kvdelete_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvdelete_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvdelete_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KVStore_kvdelete_pargs {
 public:


  virtual ~KVStore_kvdelete_pargs() throw();
  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvdelete_result__isset {
  _KVStore_kvdelete_result__isset() : success(false) {}
  bool success :1;
} _KVStore_kvdelete_result__isset;

class KVStore_kvdelete_result {
 public:

  KVStore_kvdelete_result(const KVStore_kvdelete_result&);
  KVStore_kvdelete_result& operator=(const KVStore_kvdelete_result&);
  KVStore_kvdelete_result() {
  }

  virtual ~KVStore_kvdelete_result() throw();
  Result success;

  _KVStore_kvdelete_result__isset __isset;

  void __set_success(const Result& val);

  bool operator == (const KVStore_kvdelete_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KVStore_kvdelete_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KVStore_kvdelete_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KVStore_kvdelete_presult__isset {
  _KVStore_kvdelete_presult__isset() : success(false) {}
  bool success :1;
} _KVStore_kvdelete_presult__isset;

class KVStore_kvdelete_presult {
 public:


  virtual ~KVStore_kvdelete_presult() throw();
  Result* success;

  _KVStore_kvdelete_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class KVStoreClient : virtual public KVStoreIf {
 public:
  KVStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  KVStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void kvset(Result& _return, const std::string& key, const std::string& value);
  void send_kvset(const std::string& key, const std::string& value);
  void recv_kvset(Result& _return);
  void kvget(Result& _return, const std::string& key);
  void send_kvget(const std::string& key);
  void recv_kvget(Result& _return);
  void kvdelete(Result& _return, const std::string& key);
  void send_kvdelete(const std::string& key);
  void recv_kvdelete(Result& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class KVStoreProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<KVStoreIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (KVStoreProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_kvset(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_kvget(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_kvdelete(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  KVStoreProcessor(boost::shared_ptr<KVStoreIf> iface) :
    iface_(iface) {
    processMap_["kvset"] = &KVStoreProcessor::process_kvset;
    processMap_["kvget"] = &KVStoreProcessor::process_kvget;
    processMap_["kvdelete"] = &KVStoreProcessor::process_kvdelete;
  }

  virtual ~KVStoreProcessor() {}
};

class KVStoreProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  KVStoreProcessorFactory(const ::boost::shared_ptr< KVStoreIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< KVStoreIfFactory > handlerFactory_;
};

class KVStoreMultiface : virtual public KVStoreIf {
 public:
  KVStoreMultiface(std::vector<boost::shared_ptr<KVStoreIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~KVStoreMultiface() {}
 protected:
  std::vector<boost::shared_ptr<KVStoreIf> > ifaces_;
  KVStoreMultiface() {}
  void add(boost::shared_ptr<KVStoreIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void kvset(Result& _return, const std::string& key, const std::string& value) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->kvset(_return, key, value);
    }
    ifaces_[i]->kvset(_return, key, value);
    return;
  }

  void kvget(Result& _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->kvget(_return, key);
    }
    ifaces_[i]->kvget(_return, key);
    return;
  }

  void kvdelete(Result& _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->kvdelete(_return, key);
    }
    ifaces_[i]->kvdelete(_return, key);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class KVStoreConcurrentClient : virtual public KVStoreIf {
 public:
  KVStoreConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  KVStoreConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void kvset(Result& _return, const std::string& key, const std::string& value);
  int32_t send_kvset(const std::string& key, const std::string& value);
  void recv_kvset(Result& _return, const int32_t seqid);
  void kvget(Result& _return, const std::string& key);
  int32_t send_kvget(const std::string& key);
  void recv_kvget(Result& _return, const int32_t seqid);
  void kvdelete(Result& _return, const std::string& key);
  int32_t send_kvdelete(const std::string& key);
  void recv_kvdelete(Result& _return, const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
