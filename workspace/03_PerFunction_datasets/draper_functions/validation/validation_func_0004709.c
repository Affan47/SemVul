f_phylumofwithcasesinfo
#ifdef KC_USE_PROTOTYPES
(withcasesinfo wcso)
#else
(wcso) withcasesinfo wcso;
#endif
#line 161 "../gutil.k"
{
    ID id;
    {
#line 163 "../gutil.k"
withcasesinfo kc_selvar_0_1 =
 wcso
;
#line 163 "../gutil.k"

assert_withcasesinfo(kc_selvar_0_1, "with_expression (1)");

#line 414 "gutil.c"
		if (( kc_selvar_0_1->prod_sel == sel_Conswithcasesinfo)) {
#line 168 "../gutil.k"
		withcaseinfo wco =  kc_selvar_0_1->u.Conswithcasesinfo.withcaseinfo_1;
#line 168 "../gutil.k"
		withcasesinfo r_wcso =  kc_selvar_0_1->u.Conswithcasesinfo.withcasesinfo_1;
#line 168 "../gutil.k"

	    {
#line 169 "../gutil.k"
withcaseinfo kc_selvar_1_1 =
 wco
;
#line 169 "../gutil.k"

assert_withcaseinfo(kc_selvar_1_1, "with_expression (1)");

#line 431 "gutil.c"
		if (( kc_selvar_1_1->prod_sel == sel_Withcaseinfo)) {
#line 170 "../gutil.k"
		patternrepresentation patrep =  kc_selvar_1_1->u.Withcaseinfo.patternrepresentation_1;
#line 170 "../gutil.k"

		    if ( eq_ID(id = f_phylumofpatternrepresentation( patrep ), f_emptyId() )) {
			return f_phylumofwithcasesinfo( r_wcso );
		    } else {
			return id;
}
#line 442 "gutil.c"
		} else
{ kc_no_default_in_with( "f_phylumofwithcasesinfo", __LINE__, __FILE__ );
   return (ID)0; }
}
#line 175 "../gutil.k"

#line 449 "gutil.c"
		} else
		if (( kc_selvar_0_1->prod_sel == sel_Nilwithcasesinfo)) {
#line 164 "../gutil.k"

	    v_report(NonFatal( NoFileLine(), Problem1S( "Error: can not find type of with expression" )));
	    return Id( Str( mkcasestring( "KC_ERRORunknownTYPE" )));

#line 457 "gutil.c"
		} else
{ kc_no_default_in_with( "f_phylumofwithcasesinfo", __LINE__, __FILE__ );
   return (ID)0; }
}
#line 175 "../gutil.k"

#line 175 "../gutil.k"
}
