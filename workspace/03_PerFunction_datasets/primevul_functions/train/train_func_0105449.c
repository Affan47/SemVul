STATIC SV *
S_get_fq_name(pTHX_
              const char * const name,
              const Size_t name_len,
              const bool is_utf8,
              const bool has_colon_colon
             )
{


    SV * fq_name;

    fq_name = newSVpvs_flags("", SVs_TEMP);


    if (! has_colon_colon) {
        const HV * pkg = (IN_PERL_COMPILETIME)
                         ? PL_curstash
                         : CopSTASH(PL_curcop);
        const char* pkgname = HvNAME(pkg);

        Perl_sv_catpvf(aTHX_ fq_name, "%" UTF8f,
                      UTF8fARG(is_utf8, strlen(pkgname), pkgname));
        sv_catpvs(fq_name, "::");
    }

    Perl_sv_catpvf(aTHX_ fq_name, "%" UTF8f,
                         UTF8fARG(is_utf8, name_len, name));
    return fq_name;
}
