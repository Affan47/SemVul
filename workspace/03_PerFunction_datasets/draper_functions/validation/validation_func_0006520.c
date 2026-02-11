luaU_undump (lua_State* L, ZIO* Z, Mbuffer* buff, const char* name)
{
 LoadState S;
 Closure* cl;
 if (*name=='@' || *name=='=')
  S.name=name+1;
 else if (*name==LUA_SIGNATURE[0])
  S.name="binary string";
 else
  S.name=name;
 S.L=L;
 S.Z=Z;
 S.b=buff;
 LoadHeader(&S);
 cl=luaF_newLclosure(L,1);
 setclLvalue(L,L->top,cl); incr_top(L);
 cl->l.p=luaF_newproto(L);
 LoadFunction(&S,cl->l.p);
 if (cl->l.p->sizeupvalues != 1)
 {
  Proto* p=cl->l.p;
  cl=luaF_newLclosure(L,cl->l.p->sizeupvalues);
  cl->l.p=p;
  setclLvalue(L,L->top-1,cl);
 }
 luai_verifycode(L,buff,cl->l.p);
 return cl;
}
