AsciiWrite(const Arguments &args) {
  HandleScope scope;

  Buffer *buffer = ObjectWrap::Unwrap<Buffer>(args.This());

  if (!args[0]->IsString()) {
    return ThrowException(Exception::TypeError(String::New(
            "Argument must be a string")));
  }

  Local<String> s = args[0]->ToString();

  size_t offset = args[1]->Int32Value();

  if (s->Length() > 0 && offset >= buffer->length_) {
    return ThrowException(Exception::TypeError(String::New(
            "Offset is out of bounds")));
  }

  size_t max_length = args[2]->IsUndefined() ? buffer->length_ - offset
                                             : args[2]->Uint32Value();
  max_length = MIN(s->Length(), MIN(buffer->length_ - offset, max_length));

  char *p = buffer->data_ + offset;

  int written = s->WriteAscii(p,
                              0,
                              max_length,
                              (String::HINT_MANY_WRITES_EXPECTED |
                               String::NO_NULL_TERMINATION));

  constructor_template->GetFunction()->Set(chars_written_sym,
                                           Integer::New(written));

  return scope.Close(Integer::New(written));
}
