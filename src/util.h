#pragma once
#include <fcntl.h>
#include <unistd.h>
#include "v8.h"
#include "include/libplatform/libplatform.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include <cstddef>
#include <iostream>


using namespace v8;

template <typename T, size_t N>
constexpr size_t arraysize(const T (&)[N]) {
    return N;
}

namespace my_node
{

        #define MV(module) \
        module::Initialize(isolate, global, context);


        #define MOLEULES_LIST(V) \
        V(Console1)              \
        V(File)                  \
        V(OS)

        template <typename T, size_t kStackStorageSize = 1024>
class MaybeStackBuffer {
 public:
  const T* out() const {
    return buf_;
  }

  T* out() {
    return buf_;
  }

  // operator* for compatibility with `v8::String::(Utf8)Value`
  T* operator*() {
    return buf_;
  }

  const T* operator*() const {
    return buf_;
  }

  T& operator[](size_t index) {
    // CHECK_LT(index, length());
    return buf_[index];
  }

  const T& operator[](size_t index) const {
    // CHECK_LT(index, length());
    return buf_[index];
  }

  size_t length() const {
    return length_;
  }

  // Current maximum capacity of the buffer with which SetLength() can be used
  // without first calling AllocateSufficientStorage().
  size_t capacity() const {
    return capacity_;
  }

  // Make sure enough space for `storage` entries is available.
  // This method can be called multiple times throughout the lifetime of the
  // buffer, but once this has been called Invalidate() cannot be used.
  // Content of the buffer in the range [0, length()) is preserved.
  void AllocateSufficientStorage(size_t storage);

  void SetLength(size_t length) {
    // capacity() returns how much memory is actually available.
    // CHECK_LE(length, capacity());
    length_ = length;
  }

  void SetLengthAndZeroTerminate(size_t length) {
    // capacity() returns how much memory is actually available.
    // CHECK_LE(length + 1, capacity());
    SetLength(length);

    // T() is 0 for integer types, nullptr for pointers, etc.
    buf_[length] = T();
  }

  // Make dereferencing this object return nullptr.
  // This method can be called multiple times throughout the lifetime of the
  // buffer, but once this has been called AllocateSufficientStorage() cannot
  // be used.
  void Invalidate() {
    // CHECK(!IsAllocated());
    capacity_ = 0;
    length_ = 0;
    buf_ = nullptr;
  }

  // If the buffer is stored in the heap rather than on the stack.
  bool IsAllocated() const {
    return !IsInvalidated() && buf_ != buf_st_;
  }

  // If Invalidate() has been called.
  bool IsInvalidated() const {
    return buf_ == nullptr;
  }

  // Release ownership of the malloc'd buffer.
  // Note: This does not free the buffer.
  void Release() {
    buf_ = buf_st_;
    length_ = 0;
    capacity_ = arraysize(buf_st_);
  }

  MaybeStackBuffer()
      : length_(0), capacity_(arraysize(buf_st_)), buf_(buf_st_) {
    // Default to a zero-length, null-terminated buffer.
    buf_[0] = T();
  }

  explicit MaybeStackBuffer(size_t storage) : MaybeStackBuffer() {
    AllocateSufficientStorage(storage);
  }

  ~MaybeStackBuffer() {
    if (IsAllocated())
      free(buf_);
  }

  inline std::basic_string<T> ToString() const { return {out(), length()}; }
  inline std::basic_string_view<T> ToStringView() const {
    return {out(), length()};
  }

 private:
  size_t length_;
  // capacity of the malloc'ed buf_
  size_t capacity_;
  T* buf_;
  T buf_st_[kStackStorageSize];
};
        void setMethod(Isolate *isolate,
                        Local<ObjectTemplate>
                        recv, const char *name,
                        FunctionCallback callback);

        void register_builtins(Isolate * isolate, Local<Object> global, Local<Context> context);
        std::string ToString(Local<Value> value);
        inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                           const char* data,
                                           int length) {
            return v8::String::NewFromOneByte(isolate,
                                              reinterpret_cast<const uint8_t*>(data),
                                              v8::NewStringType::kNormal,
                                              length).ToLocalChecked();
        }

        // Convenience wrapper around v8::String::NewFromOneByte().
        inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                               const char* data,
                                               int length = -1);
    void generateErrorMessage(Isolate* isolate, char* msg);
    void makeUTF8String(v8::Local<v8::String> value);
  std::string makeUTF8String(Isolate *isolate, v8::Local<v8::Value> value);
}
