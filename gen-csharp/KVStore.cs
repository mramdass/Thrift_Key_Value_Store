/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

public partial class KVStore {
  public interface Iface {
    Result kvset(string key, string @value);
    #if SILVERLIGHT
    IAsyncResult Begin_kvset(AsyncCallback callback, object state, string key, string @value);
    Result End_kvset(IAsyncResult asyncResult);
    #endif
    Result kvget(string key);
    #if SILVERLIGHT
    IAsyncResult Begin_kvget(AsyncCallback callback, object state, string key);
    Result End_kvget(IAsyncResult asyncResult);
    #endif
    Result kvdelete(string key);
    #if SILVERLIGHT
    IAsyncResult Begin_kvdelete(AsyncCallback callback, object state, string key);
    Result End_kvdelete(IAsyncResult asyncResult);
    #endif
  }

  public class Client : IDisposable, Iface {
    public Client(TProtocol prot) : this(prot, prot)
    {
    }

    public Client(TProtocol iprot, TProtocol oprot)
    {
      iprot_ = iprot;
      oprot_ = oprot;
    }

    protected TProtocol iprot_;
    protected TProtocol oprot_;
    protected int seqid_;

    public TProtocol InputProtocol
    {
      get { return iprot_; }
    }
    public TProtocol OutputProtocol
    {
      get { return oprot_; }
    }


    #region " IDisposable Support "
    private bool _IsDisposed;

    // IDisposable
    public void Dispose()
    {
      Dispose(true);
    }
    

    protected virtual void Dispose(bool disposing)
    {
      if (!_IsDisposed)
      {
        if (disposing)
        {
          if (iprot_ != null)
          {
            ((IDisposable)iprot_).Dispose();
          }
          if (oprot_ != null)
          {
            ((IDisposable)oprot_).Dispose();
          }
        }
      }
      _IsDisposed = true;
    }
    #endregion


    
    #if SILVERLIGHT
    public IAsyncResult Begin_kvset(AsyncCallback callback, object state, string key, string @value)
    {
      return send_kvset(callback, state, key, @value);
    }

    public Result End_kvset(IAsyncResult asyncResult)
    {
      oprot_.Transport.EndFlush(asyncResult);
      return recv_kvset();
    }

    #endif

    public Result kvset(string key, string @value)
    {
      #if !SILVERLIGHT
      send_kvset(key, @value);
      return recv_kvset();

      #else
      var asyncResult = Begin_kvset(null, null, key, @value);
      return End_kvset(asyncResult);

      #endif
    }
    #if SILVERLIGHT
    public IAsyncResult send_kvset(AsyncCallback callback, object state, string key, string @value)
    #else
    public void send_kvset(string key, string @value)
    #endif
    {
      oprot_.WriteMessageBegin(new TMessage("kvset", TMessageType.Call, seqid_));
      kvset_args args = new kvset_args();
      args.Key = key;
      args.Value = @value;
      args.Write(oprot_);
      oprot_.WriteMessageEnd();
      #if SILVERLIGHT
      return oprot_.Transport.BeginFlush(callback, state);
      #else
      oprot_.Transport.Flush();
      #endif
    }

    public Result recv_kvset()
    {
      TMessage msg = iprot_.ReadMessageBegin();
      if (msg.Type == TMessageType.Exception) {
        TApplicationException x = TApplicationException.Read(iprot_);
        iprot_.ReadMessageEnd();
        throw x;
      }
      kvset_result result = new kvset_result();
      result.Read(iprot_);
      iprot_.ReadMessageEnd();
      if (result.__isset.success) {
        return result.Success;
      }
      throw new TApplicationException(TApplicationException.ExceptionType.MissingResult, "kvset failed: unknown result");
    }

    
    #if SILVERLIGHT
    public IAsyncResult Begin_kvget(AsyncCallback callback, object state, string key)
    {
      return send_kvget(callback, state, key);
    }

    public Result End_kvget(IAsyncResult asyncResult)
    {
      oprot_.Transport.EndFlush(asyncResult);
      return recv_kvget();
    }

    #endif

    public Result kvget(string key)
    {
      #if !SILVERLIGHT
      send_kvget(key);
      return recv_kvget();

      #else
      var asyncResult = Begin_kvget(null, null, key);
      return End_kvget(asyncResult);

      #endif
    }
    #if SILVERLIGHT
    public IAsyncResult send_kvget(AsyncCallback callback, object state, string key)
    #else
    public void send_kvget(string key)
    #endif
    {
      oprot_.WriteMessageBegin(new TMessage("kvget", TMessageType.Call, seqid_));
      kvget_args args = new kvget_args();
      args.Key = key;
      args.Write(oprot_);
      oprot_.WriteMessageEnd();
      #if SILVERLIGHT
      return oprot_.Transport.BeginFlush(callback, state);
      #else
      oprot_.Transport.Flush();
      #endif
    }

    public Result recv_kvget()
    {
      TMessage msg = iprot_.ReadMessageBegin();
      if (msg.Type == TMessageType.Exception) {
        TApplicationException x = TApplicationException.Read(iprot_);
        iprot_.ReadMessageEnd();
        throw x;
      }
      kvget_result result = new kvget_result();
      result.Read(iprot_);
      iprot_.ReadMessageEnd();
      if (result.__isset.success) {
        return result.Success;
      }
      throw new TApplicationException(TApplicationException.ExceptionType.MissingResult, "kvget failed: unknown result");
    }

    
    #if SILVERLIGHT
    public IAsyncResult Begin_kvdelete(AsyncCallback callback, object state, string key)
    {
      return send_kvdelete(callback, state, key);
    }

    public Result End_kvdelete(IAsyncResult asyncResult)
    {
      oprot_.Transport.EndFlush(asyncResult);
      return recv_kvdelete();
    }

    #endif

    public Result kvdelete(string key)
    {
      #if !SILVERLIGHT
      send_kvdelete(key);
      return recv_kvdelete();

      #else
      var asyncResult = Begin_kvdelete(null, null, key);
      return End_kvdelete(asyncResult);

      #endif
    }
    #if SILVERLIGHT
    public IAsyncResult send_kvdelete(AsyncCallback callback, object state, string key)
    #else
    public void send_kvdelete(string key)
    #endif
    {
      oprot_.WriteMessageBegin(new TMessage("kvdelete", TMessageType.Call, seqid_));
      kvdelete_args args = new kvdelete_args();
      args.Key = key;
      args.Write(oprot_);
      oprot_.WriteMessageEnd();
      #if SILVERLIGHT
      return oprot_.Transport.BeginFlush(callback, state);
      #else
      oprot_.Transport.Flush();
      #endif
    }

    public Result recv_kvdelete()
    {
      TMessage msg = iprot_.ReadMessageBegin();
      if (msg.Type == TMessageType.Exception) {
        TApplicationException x = TApplicationException.Read(iprot_);
        iprot_.ReadMessageEnd();
        throw x;
      }
      kvdelete_result result = new kvdelete_result();
      result.Read(iprot_);
      iprot_.ReadMessageEnd();
      if (result.__isset.success) {
        return result.Success;
      }
      throw new TApplicationException(TApplicationException.ExceptionType.MissingResult, "kvdelete failed: unknown result");
    }

  }
  public class Processor : TProcessor {
    public Processor(Iface iface)
    {
      iface_ = iface;
      processMap_["kvset"] = kvset_Process;
      processMap_["kvget"] = kvget_Process;
      processMap_["kvdelete"] = kvdelete_Process;
    }

    protected delegate void ProcessFunction(int seqid, TProtocol iprot, TProtocol oprot);
    private Iface iface_;
    protected Dictionary<string, ProcessFunction> processMap_ = new Dictionary<string, ProcessFunction>();

    public bool Process(TProtocol iprot, TProtocol oprot)
    {
      try
      {
        TMessage msg = iprot.ReadMessageBegin();
        ProcessFunction fn;
        processMap_.TryGetValue(msg.Name, out fn);
        if (fn == null) {
          TProtocolUtil.Skip(iprot, TType.Struct);
          iprot.ReadMessageEnd();
          TApplicationException x = new TApplicationException (TApplicationException.ExceptionType.UnknownMethod, "Invalid method name: '" + msg.Name + "'");
          oprot.WriteMessageBegin(new TMessage(msg.Name, TMessageType.Exception, msg.SeqID));
          x.Write(oprot);
          oprot.WriteMessageEnd();
          oprot.Transport.Flush();
          return true;
        }
        fn(msg.SeqID, iprot, oprot);
      }
      catch (IOException)
      {
        return false;
      }
      return true;
    }

    public void kvset_Process(int seqid, TProtocol iprot, TProtocol oprot)
    {
      kvset_args args = new kvset_args();
      args.Read(iprot);
      iprot.ReadMessageEnd();
      kvset_result result = new kvset_result();
      result.Success = iface_.kvset(args.Key, args.Value);
      oprot.WriteMessageBegin(new TMessage("kvset", TMessageType.Reply, seqid)); 
      result.Write(oprot);
      oprot.WriteMessageEnd();
      oprot.Transport.Flush();
    }

    public void kvget_Process(int seqid, TProtocol iprot, TProtocol oprot)
    {
      kvget_args args = new kvget_args();
      args.Read(iprot);
      iprot.ReadMessageEnd();
      kvget_result result = new kvget_result();
      result.Success = iface_.kvget(args.Key);
      oprot.WriteMessageBegin(new TMessage("kvget", TMessageType.Reply, seqid)); 
      result.Write(oprot);
      oprot.WriteMessageEnd();
      oprot.Transport.Flush();
    }

    public void kvdelete_Process(int seqid, TProtocol iprot, TProtocol oprot)
    {
      kvdelete_args args = new kvdelete_args();
      args.Read(iprot);
      iprot.ReadMessageEnd();
      kvdelete_result result = new kvdelete_result();
      result.Success = iface_.kvdelete(args.Key);
      oprot.WriteMessageBegin(new TMessage("kvdelete", TMessageType.Reply, seqid)); 
      result.Write(oprot);
      oprot.WriteMessageEnd();
      oprot.Transport.Flush();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvset_args : TBase
  {
    private string _key;
    private string _value;

    public string Key
    {
      get
      {
        return _key;
      }
      set
      {
        __isset.key = true;
        this._key = value;
      }
    }

    public string Value
    {
      get
      {
        return _value;
      }
      set
      {
        __isset.@value = true;
        this._value = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool key;
      public bool @value;
    }

    public kvset_args() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 1:
              if (field.Type == TType.String) {
                Key = iprot.ReadString();
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            case 2:
              if (field.Type == TType.String) {
                Value = iprot.ReadString();
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvset_args");
        oprot.WriteStructBegin(struc);
        TField field = new TField();
        if (Key != null && __isset.key) {
          field.Name = "key";
          field.Type = TType.String;
          field.ID = 1;
          oprot.WriteFieldBegin(field);
          oprot.WriteString(Key);
          oprot.WriteFieldEnd();
        }
        if (Value != null && __isset.@value) {
          field.Name = "value";
          field.Type = TType.String;
          field.ID = 2;
          oprot.WriteFieldBegin(field);
          oprot.WriteString(Value);
          oprot.WriteFieldEnd();
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvset_args(");
      bool __first = true;
      if (Key != null && __isset.key) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Key: ");
        __sb.Append(Key);
      }
      if (Value != null && __isset.@value) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Value: ");
        __sb.Append(Value);
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvset_result : TBase
  {
    private Result _success;

    public Result Success
    {
      get
      {
        return _success;
      }
      set
      {
        __isset.success = true;
        this._success = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool success;
    }

    public kvset_result() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 0:
              if (field.Type == TType.Struct) {
                Success = new Result();
                Success.Read(iprot);
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvset_result");
        oprot.WriteStructBegin(struc);
        TField field = new TField();

        if (this.__isset.success) {
          if (Success != null) {
            field.Name = "Success";
            field.Type = TType.Struct;
            field.ID = 0;
            oprot.WriteFieldBegin(field);
            Success.Write(oprot);
            oprot.WriteFieldEnd();
          }
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvset_result(");
      bool __first = true;
      if (Success != null && __isset.success) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Success: ");
        __sb.Append(Success== null ? "<null>" : Success.ToString());
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvget_args : TBase
  {
    private string _key;

    public string Key
    {
      get
      {
        return _key;
      }
      set
      {
        __isset.key = true;
        this._key = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool key;
    }

    public kvget_args() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 1:
              if (field.Type == TType.String) {
                Key = iprot.ReadString();
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvget_args");
        oprot.WriteStructBegin(struc);
        TField field = new TField();
        if (Key != null && __isset.key) {
          field.Name = "key";
          field.Type = TType.String;
          field.ID = 1;
          oprot.WriteFieldBegin(field);
          oprot.WriteString(Key);
          oprot.WriteFieldEnd();
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvget_args(");
      bool __first = true;
      if (Key != null && __isset.key) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Key: ");
        __sb.Append(Key);
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvget_result : TBase
  {
    private Result _success;

    public Result Success
    {
      get
      {
        return _success;
      }
      set
      {
        __isset.success = true;
        this._success = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool success;
    }

    public kvget_result() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 0:
              if (field.Type == TType.Struct) {
                Success = new Result();
                Success.Read(iprot);
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvget_result");
        oprot.WriteStructBegin(struc);
        TField field = new TField();

        if (this.__isset.success) {
          if (Success != null) {
            field.Name = "Success";
            field.Type = TType.Struct;
            field.ID = 0;
            oprot.WriteFieldBegin(field);
            Success.Write(oprot);
            oprot.WriteFieldEnd();
          }
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvget_result(");
      bool __first = true;
      if (Success != null && __isset.success) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Success: ");
        __sb.Append(Success== null ? "<null>" : Success.ToString());
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvdelete_args : TBase
  {
    private string _key;

    public string Key
    {
      get
      {
        return _key;
      }
      set
      {
        __isset.key = true;
        this._key = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool key;
    }

    public kvdelete_args() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 1:
              if (field.Type == TType.String) {
                Key = iprot.ReadString();
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvdelete_args");
        oprot.WriteStructBegin(struc);
        TField field = new TField();
        if (Key != null && __isset.key) {
          field.Name = "key";
          field.Type = TType.String;
          field.ID = 1;
          oprot.WriteFieldBegin(field);
          oprot.WriteString(Key);
          oprot.WriteFieldEnd();
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvdelete_args(");
      bool __first = true;
      if (Key != null && __isset.key) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Key: ");
        __sb.Append(Key);
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }


  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class kvdelete_result : TBase
  {
    private Result _success;

    public Result Success
    {
      get
      {
        return _success;
      }
      set
      {
        __isset.success = true;
        this._success = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool success;
    }

    public kvdelete_result() {
    }

    public void Read (TProtocol iprot)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        TField field;
        iprot.ReadStructBegin();
        while (true)
        {
          field = iprot.ReadFieldBegin();
          if (field.Type == TType.Stop) { 
            break;
          }
          switch (field.ID)
          {
            case 0:
              if (field.Type == TType.Struct) {
                Success = new Result();
                Success.Read(iprot);
              } else { 
                TProtocolUtil.Skip(iprot, field.Type);
              }
              break;
            default: 
              TProtocolUtil.Skip(iprot, field.Type);
              break;
          }
          iprot.ReadFieldEnd();
        }
        iprot.ReadStructEnd();
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public void Write(TProtocol oprot) {
      oprot.IncrementRecursionDepth();
      try
      {
        TStruct struc = new TStruct("kvdelete_result");
        oprot.WriteStructBegin(struc);
        TField field = new TField();

        if (this.__isset.success) {
          if (Success != null) {
            field.Name = "Success";
            field.Type = TType.Struct;
            field.ID = 0;
            oprot.WriteFieldBegin(field);
            Success.Write(oprot);
            oprot.WriteFieldEnd();
          }
        }
        oprot.WriteFieldStop();
        oprot.WriteStructEnd();
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override string ToString() {
      StringBuilder __sb = new StringBuilder("kvdelete_result(");
      bool __first = true;
      if (Success != null && __isset.success) {
        if(!__first) { __sb.Append(", "); }
        __first = false;
        __sb.Append("Success: ");
        __sb.Append(Success== null ? "<null>" : Success.ToString());
      }
      __sb.Append(")");
      return __sb.ToString();
    }

  }

}
