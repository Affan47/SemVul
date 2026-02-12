static void trace_flushroot(jit_State *J, GCtrace *T)
{
  GCproto *pt = &gcref(T->startpt)->pt;
  lua_assert(T->root == 0 && pt != NULL);

  trace_unpatch(J, T);

  if (pt->trace == T->traceno) {
    pt->trace = T->nextroot;
  } else if (pt->trace) {
    GCtrace *T2 = traceref(J, pt->trace);
    if (T2) {
      for (; T2->nextroot; T2 = traceref(J, T2->nextroot))
	if (T2->nextroot == T->traceno) {
	  T2->nextroot = T->nextroot;
	  break;
	}
    }
  }
}
