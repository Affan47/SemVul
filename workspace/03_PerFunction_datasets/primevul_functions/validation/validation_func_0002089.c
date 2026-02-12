SimpleParser(const char* input, int length, TypedValue* buffer,
               JSONContainerType container_type, bool is_tsimplejson)
    : p(input)
    , top(buffer)
    , array_depth(-kMaxArrayDepth)
    , container_type(container_type)
    , is_tsimplejson(is_tsimplejson)
  {
    assertx(input[length] == 0);
  }
