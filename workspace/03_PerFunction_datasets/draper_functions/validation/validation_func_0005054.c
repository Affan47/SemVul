cpl_column_pow_double_complex(cpl_column *column, double exponent)
{

    cpl_size        nullcount = cpl_column_count_invalid(column);
    cpl_size        length    = cpl_column_get_size(column);
    double complex *dp        = cpl_column_get_data_double_complex(column);
    int            *np        = cpl_column_get_data_invalid(column);
    int             negative  = exponent < 0.0;
    cpl_size        i;

    if (nullcount == length)
        return;

    if (exponent != 1.0) {
        if (nullcount == 0) {
            if (negative) {
                for (i = 0; i < length; i++, dp++) {
                    if (cabs(*dp) > 0.0) {
                        double complex value = cpow(*dp, -exponent);
                        if (value != 0.0) {
                            *dp = 1 / value;
                        }
                        else {
                            cpl_column_set_invalid(column, i);
                        }
                    }
                    else {
                        cpl_column_set_invalid(column, i);
                    }
                }
            }
            else {
                for (i = 0; i < length; i++, dp++) {
                    *dp = cpow(*dp, exponent);
                }
            }
        }
        else {
            for (i = 0; i < length; i++, dp++, np++) {
                if (negative) {
                    if (*np == 0) {
                        if (cabs(*dp) > 0.0) {
                            double complex value = cpow(*dp, -exponent);
                            if (value != 0.0) {
                                *dp = 1 / value;
                            }
                            else {
                                cpl_column_set_invalid(column, i);
                            }
                        }
                        else {
                            cpl_column_set_invalid(column, i);
                        }
                    }
                }
                else {
                    if (*np == 0) {
                        *dp = cpow(*dp, exponent);
                    }
                }
            }
        }
    }
}
