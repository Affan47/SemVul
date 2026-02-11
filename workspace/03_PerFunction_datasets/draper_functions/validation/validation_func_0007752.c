v_module_instantiation(void)
#else
v_module_instantiation()
#endif
{
#line 1694 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1694 "./verilog.g"
  v_name_of_module();
#line 1695 "./verilog.g"

  if(!module_is_duplicate)
  {
    add_string_to_tree(modname_tree, zzaArg(zztasp1,1 ).symbol->name, FALSE);
    if(comp_type_name)
    {
      free(comp_type_name);
    }
    comp_type_name = strdup(zzaArg(zztasp1,1 ).symbol->name);
  }
#line 1706 "./verilog.g"
  v_parameter_value_assignment();
#line 1707 "./verilog.g"
  v_module_instance();
#line 1708 "./verilog.g"
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==V_COMMA) ) {
#line 1708 "./verilog.g"
      zzmatch(V_COMMA); zzCONSUME;
#line 1708 "./verilog.g"
      v_module_instance();
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
#line 1708 "./verilog.g"
  zzmatch(V_SEMI);
#line 1709 "./verilog.g"

  if(comp_type_name)
  {
    free(comp_type_name);
    comp_type_name = NULL;
  }
 zzCONSUME;

  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd20, 0x20);
  }
}
