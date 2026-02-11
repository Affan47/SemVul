Perl_sub_crush_depth(pTHX_ CV *cv)
{
    PERL_ARGS_ASSERT_SUB_CRUSH_DEPTH;

    if (CvANON(cv))
	Perl_warner(aTHX_ packWARN(WARN_RECURSION), "Deep recursion on anonymous subroutine");
    else {
        HEK *const hek = CvNAME_HEK(cv);
        SV *tmpstr;
        if (hek) {
            tmpstr = sv_2mortal(newSVhek(hek));
        }
        else {
            tmpstr = sv_newmortal();
            gv_efullname3(tmpstr, CvGV(cv), NULL);
        }
	Perl_warner(aTHX_ packWARN(WARN_RECURSION), "Deep recursion on subroutine \"%"SVf"\"",
		    SVfARG(tmpstr));
    }
}
