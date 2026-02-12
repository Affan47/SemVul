static void *err_unwind(lua_State *L, void *stopcf, int errcode)
{
  TValue *frame = L->base-1;
  void *cf = L->cframe;
  while (cf) {
    int32_t nres = cframe_nres(cframe_raw(cf));
    if (nres < 0) {
      TValue *top = restorestack(L, -nres);
      if (frame < top) {
	if (errcode) {
	  L->cframe = cframe_prev(cf);
	  L->base = frame+1;
	  unwindstack(L, top);
	}
	return cf;
      }
    }
    if (frame <= tvref(L->stack))
      break;
    switch (frame_typep(frame)) {
    case FRAME_LUA:
    case FRAME_LUAP:
      frame = frame_prevl(frame);
      break;
    case FRAME_C:
#if LJ_HASFFI
    unwind_c:
#endif
#if LJ_UNWIND_EXT
      if (errcode) {
	L->cframe = cframe_prev(cf);
	L->base = frame_prevd(frame) + 1;
	unwindstack(L, frame);
      } else if (cf != stopcf) {
	cf = cframe_prev(cf);
	frame = frame_prevd(frame);
	break;
      }
      return NULL;
#else
      UNUSED(stopcf);
      cf = cframe_prev(cf);
      frame = frame_prevd(frame);
      break;
#endif
    case FRAME_CP:
      if (cframe_canyield(cf)) {
	if (errcode) {
	  hook_leave(G(L));
	  L->cframe = NULL;
	  L->status = (uint8_t)errcode;
	}
	return cf;
      }
      if (errcode) {
	L->cframe = cframe_prev(cf);
	L->base = frame_prevd(frame) + 1;
	unwindstack(L, frame);
      }
      return cf;
    case FRAME_CONT:
#if LJ_HASFFI
      if ((frame-1)->u32.lo == LJ_CONT_FFI_CALLBACK)
	goto unwind_c;
#endif

    case FRAME_VARG:
      frame = frame_prevd(frame);
      break;
    case FRAME_PCALL:
    case FRAME_PCALLH:
      if (errcode) {
	if (errcode == LUA_YIELD) {
	  frame = frame_prevd(frame);
	  break;
	}
	if (frame_typep(frame) == FRAME_PCALL)
	  hook_leave(G(L));
	L->cframe = cf;
	L->base = frame_prevd(frame) + 1;
	unwindstack(L, L->base);
      }
      return (void *)((intptr_t)cf | CFRAME_UNWIND_FF);
    }
  }

  if (errcode) {
    L->cframe = NULL;
    L->base = tvref(L->stack)+1;
    unwindstack(L, L->base);
    if (G(L)->panic)
      G(L)->panic(L);
    exit(EXIT_FAILURE);
  }
  return L;
}
