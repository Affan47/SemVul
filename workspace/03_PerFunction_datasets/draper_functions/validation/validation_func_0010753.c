S_no_fh_allowed(pTHX_ OP *o)
{
    PERL_ARGS_ASSERT_NO_FH_ALLOWED;

    yyerror(Perl_form(aTHX_ "Missing comma after first argument to %s function",
		 OP_DESC(o)));
    return o;
}
