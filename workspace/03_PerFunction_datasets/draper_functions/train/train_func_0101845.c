pecalc_l(III_psy_ratio const *mr, FLOAT masking_lower)
{
    FLOAT   pe_l;
    static const FLOAT regcoef_l[] = {
        6.8,
        5.8,
        5.8,
        6.4,
        6.5,
        9.9,
        12.1,
        14.4,
        15,
        18.9,
        21.6,
        26.9,
        34.2,
        40.2,
        46.8,
        56.5,
        60.7,
        73.9,
        85.7,
        93.4,
        126.1,

    };
    unsigned int sb;

    pe_l = 1124.23 / 4;
    for (sb = 0; sb < SBMAX_l - 1; sb++) {
        FLOAT const thm = mr->thm.l[sb];
        assert(sb < dimension_of(regcoef_l));
        if (thm > 0.0) {
            FLOAT const x = thm * masking_lower;
            FLOAT const en = mr->en.l[sb];
            if (en > x) {
                if (en > x * 1e10) {
                    pe_l += regcoef_l[sb] * (10.0 * LOG10);
                }
                else {
                    assert(x > 0);
                    pe_l += regcoef_l[sb] * FAST_LOG10(en / x);
                }
            }
        }
    }

    return pe_l;
}
