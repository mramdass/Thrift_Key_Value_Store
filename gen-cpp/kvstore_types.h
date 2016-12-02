/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef kvstore_TYPES_H
#define kvstore_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace kvstore {

struct ErrorCode {
  enum type {
    kSuccess = 0,
    kKeyNotFound = 1,
    kError = 2
  };
};

extern const std::map<int, const char*> _ErrorCode_VALUES_TO_NAMES;

class Result;

typedef struct _Result__isset {
  _Result__isset() : value(false), error(false), errortext(false) {}
  bool value :1;
  bool error :1;
  bool errortext :1;
} _Result__isset;

class Result {
 public:

  Result(const Result&);
  Result& operator=(const Result&);
  Result() : value(), error((ErrorCode::type)0), errortext() {
  }

  virtual ~Result() throw();
  std::string value;
  ErrorCode::type error;
  std::string errortext;

  _Result__isset __isset;

  void __set_value(const std::string& val);

  void __set_error(const ErrorCode::type val);

  void __set_errortext(const std::string& val);

  bool operator == (const Result & rhs) const
  {
    if (!(value == rhs.value))
      return false;
    if (!(error == rhs.error))
      return false;
    if (!(errortext == rhs.errortext))
      return false;
    return true;
  }
  bool operator != (const Result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Result &a, Result &b);

inline std::ostream& operator<<(std::ostream& out, const Result& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif
