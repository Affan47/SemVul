cdata_getconst(CTState *cts, TValue *o, CType *ct)
{
  CType *ctt = ctype_child(cts, ct);
  lua_assert(ctype_isinteger(ctt->info) && ctt->size <= 4);

  if ((ctt->info & CTF_UNSIGNED) && (int32_t)ct->size < 0)
    setnumV(o, (lua_Number)(uint32_t)ct->size);
  else
    setintV(o, (int32_t)ct->size);
}
