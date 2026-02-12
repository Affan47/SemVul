static void reallymarkobject (global_State *g, GCObject *o) {
  white2gray(o);
  switch (o->tt) {
    case LUA_VSHRSTR:
    case LUA_VLNGSTR: {
      gray2black(o);
      break;
    }
    case LUA_VUPVAL: {
      UpVal *uv = gco2upv(o);
      if (!upisopen(uv))
        gray2black(o);
      markvalue(g, uv->v);
      break;
    }
    case LUA_VUSERDATA: {
      Udata *u = gco2u(o);
      if (u->nuvalue == 0) {
        markobjectN(g, u->metatable);
        gray2black(o);
        break;
      }

    }
    case LUA_VLCL: case LUA_VCCL: case LUA_VTABLE:
    case LUA_VTHREAD: case LUA_VPROTO: {
      linkobjgclist(o, g->gray);
      break;
    }
    default: lua_assert(0); break;
  }
}
