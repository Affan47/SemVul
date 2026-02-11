calc_noise(gr_info const *const cod_info,
           FLOAT const *l3_xmin,
           FLOAT * distort, calc_noise_result * const res, calc_noise_data * prev_noise)
{
    int     sfb, l, over = 0;
    FLOAT   over_noise_db = 0;
    FLOAT   tot_noise_db = 0;
    FLOAT   max_noise = -20.0;
    int     j = 0;
    const int *scalefac = cod_info->scalefac;

    res->over_SSD = 0;


    for (sfb = 0; sfb < cod_info->psymax; sfb++) {
        int const s =
            cod_info->global_gain - (((*scalefac++) + (cod_info->preflag ? pretab[sfb] : 0))
                                     << (cod_info->scalefac_scale + 1))
            - cod_info->subblock_gain[cod_info->window[sfb]] * 8;
        FLOAT const r_l3_xmin = 1.f / *l3_xmin++;
        FLOAT   distort_ = 0.0f;
        FLOAT   noise = 0.0f;

        if (prev_noise && (prev_noise->step[sfb] == s)) {


            j += cod_info->width[sfb];
            distort_ = r_l3_xmin * prev_noise->noise[sfb];

            noise = prev_noise->noise_log[sfb];

        }
        else {
            FLOAT const step = POW20(s);
            l = cod_info->width[sfb] >> 1;

            if ((j + cod_info->width[sfb]) > cod_info->max_nonzero_coeff) {
                int     usefullsize;
                usefullsize = cod_info->max_nonzero_coeff - j + 1;

                if (usefullsize > 0)
                    l = usefullsize >> 1;
                else
                    l = 0;
            }

            noise = calc_noise_core_c(cod_info, &j, l, step);


            if (prev_noise) {

                prev_noise->step[sfb] = s;
                prev_noise->noise[sfb] = noise;
            }

            distort_ = r_l3_xmin * noise;


            noise = FAST_LOG10(Max(distort_, 1E-20f));

            if (prev_noise) {

                prev_noise->noise_log[sfb] = noise;
            }
        }
        *distort++ = distort_;

        if (prev_noise) {

            prev_noise->global_gain = cod_info->global_gain;;
        }


        tot_noise_db += noise;

        if (noise > 0.0) {
            int     tmp;

            tmp = Max((int) (noise * 10 + .5), 1);
            res->over_SSD += tmp * tmp;

            over++;


            over_noise_db += noise;
        }
        max_noise = Max(max_noise, noise);

    }

    res->over_count = over;
    res->tot_noise = tot_noise_db;
    res->over_noise = over_noise_db;
    res->max_noise = max_noise;

    return over;
}
