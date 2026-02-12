longlong val_int()
  {

    DBUG_ASSERT(fixed == 1);
    return longlong_from_hex_hybrid(str_value.ptr(), str_value.length());
  }
