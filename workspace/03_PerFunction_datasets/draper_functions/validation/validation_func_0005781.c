sql_type_cast_svpv(pTHX_ SV *sv, int sql_type, U32 flags, void *v)
{
    int cast_ok = 0;
    int grok_flags;
    UV uv;


    if (!sv || !SvOK(sv))
        return -1;

    switch(sql_type) {

    default:
        return -2;

    case SQL_INTEGER:

        sv_2iv(sv);


        cast_ok = (SvIOK(sv) && !SvNOK(sv));
        break;

    case SQL_DOUBLE:
        sv_2nv(sv);


        cast_ok = SvNOK(sv);
        break;


    case SQL_NUMERIC:

        uv = 0;
        grok_flags = grok_number(SvPVX(sv), SvCUR(sv), &uv);
        cast_ok = 1;
        if (grok_flags == IS_NUMBER_IN_UV) {
            if (uv <= IV_MAX)
                 sv_2iv(sv);
            else sv_2uv(sv);
        }
        else if (grok_flags == (IS_NUMBER_IN_UV | IS_NUMBER_NEG)
            && uv <= IV_MAX
        ) {
            sv_2iv(sv);
        }
        else if (grok_flags) {
            sv_2nv(sv);
        }
        else
            cast_ok = 0;
        break;

#if 0
    case SQL_BIGINT:
#endif
    }

    if (cast_ok) {

        if (flags & DBIstcf_DISCARD_STRING
        && SvNIOK(sv)
        && SvPVX(sv)
        ) {
            SvOOK_off(sv);
            sv_force_normal(sv);
            if (SvLEN(sv))
                Safefree(SvPVX(sv));
            SvPOK_off(sv);
            SvPV_set(sv, NULL);
            SvLEN_set(sv, 0);
            SvCUR_set(sv, 0);
        }
    }

    if (cast_ok)
        return 2;
    else if (flags & DBIstcf_STRICT)
        return 0;
    else return 1;
}
