f_attribute_in_phylym
#ifdef KC_USE_PROTOTYPES
(ID a, ID p)
#else
(a, p) ID a;
ID p;
#endif
#line 1560 "../util.k"
{
	ID t = f_typeof_attribute_in_phylym( a, p );
	if ( eq_ID( t, f_emptyId() )) {
		return False;
	} else {
		return True;
}
#line 1566 "../util.k"
}
