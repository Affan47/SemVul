v_expandrange(void)
#else
v_expandrange()
#endif
{
#line 1517 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==V_LBRACK) ) {
#line 1517 "./verilog.g"
    v_range();
  }
  else {
    if ( (LA(1)==V_SCALARED) ) {
#line 1518 "./verilog.g"
      zzmatch(V_SCALARED); zzCONSUME;
#line 1518 "./verilog.g"
      v_range();
    }
    else {
      if ( (LA(1)==V_VECTORED) ) {
#line 1519 "./verilog.g"
        zzmatch(V_VECTORED); zzCONSUME;
#line 1519 "./verilog.g"
        v_range();
      }
      else {zzFAIL(1,zzerr42,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd11, 0x20);
  }
}
