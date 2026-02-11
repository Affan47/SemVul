lj_debug_uvnamev(cTValue *o, uint32_t idx, TValue **tvp)
{
  if (tvisfunc(o)) {
    GCfunc *fn = funcV(o);
    if (isluafunc(fn)) {
      GCproto *pt = funcproto(fn);
      if (idx < pt->sizeuv) {
	*tvp = uvval(&gcref(fn->l.uvptr[idx])->uv);
	return lj_debug_uvname(pt, idx);
      }
    } else {
      if (idx < fn->c.nupvalues) {
	*tvp = &fn->c.upvalue[idx];
	return "";
      }
    }
  }
  return NULL;
}
