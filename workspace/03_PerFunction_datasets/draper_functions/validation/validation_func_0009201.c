tofloat (const TValue *obj, lua_Number *n) {
  if (ttisfloat(obj)) *n = fltvalue(obj);
  else if (ttisinteger(obj)) {
    volatile lua_Number x = cast_num(ivalue(obj));
    *n = x;
  }
  else {
    *n = 0;
    return 0;
  }
  return 1;
}
