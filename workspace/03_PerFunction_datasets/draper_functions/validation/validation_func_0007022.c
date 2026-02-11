v_markbindingid
#ifdef KC_USE_PROTOTYPES
(ID id)
#else
(id) ID id;
#endif
#line 344 "../pat.k"
{
    {
#line 345 "../pat.k"
ID kc_selvar_0_1 =
 id
;
#line 345 "../pat.k"

assert_ID(kc_selvar_0_1, "with_expression (1)");

#line 744 "pat.c"
		if (( kc_selvar_0_1->prod_sel == sel_Id)) {
#line 346 "../pat.k"
		uniqID uid =  kc_selvar_0_1->u.Id.uniqID_1;
#line 346 "../pat.k"

	    BindingIdMark( uid )->marked = True;

#line 752 "pat.c"
		} else
kc_no_default_in_with( "v_markbindingid", __LINE__, __FILE__ );
}
#line 348 "../pat.k"

#line 348 "../pat.k"
}
