static void find_model_params(Encoder *encoder,
                              const int bpc,
                              unsigned int *ncounters,
                              unsigned int *levels,
                              unsigned int *n_buckets_ptrs,
                              unsigned int *repfirst,
                              unsigned int *firstsize,
                              unsigned int *repnext,
                              unsigned int *mulsize,
                              unsigned int *nbuckets)
{
    unsigned int bsize;
    unsigned int bstart, bend = 0;
    unsigned int repcntr;


    SPICE_VERIFY(DEFevol == 1 || DEFevol == 3 || DEFevol == 5);
    spice_assert(bpc <= 8 && bpc > 0);

    *ncounters = 8;

    *levels = 0x1 << bpc;

    *n_buckets_ptrs = 0;

    switch (DEFevol) {
    case 1:
        *repfirst = 3;
        *firstsize = 1;
        *repnext = 2;
        *mulsize = 2;
        break;
    case 3:
        *repfirst = 1;
        *firstsize = 1;
        *repnext = 1;
        *mulsize = 2;
        break;
    case 5:
        *repfirst = 1;
        *firstsize = 1;
        *repnext = 1;
        *mulsize = 4;
        break;
    default:
        encoder->usr->error(encoder->usr, "findmodelparams(): DEFevol out of range!!!\n");
        return;
    }

    *nbuckets = 0;
    repcntr = *repfirst + 1;
    bsize = *firstsize;

    do {
        if (*nbuckets) {
            bstart = bend + 1;
        } else {
            bstart = 0;
        }

        if (!--repcntr) {
            repcntr = *repnext;
            bsize *= *mulsize;
        }

        bend = bstart + bsize - 1;
        if (bend + bsize >= *levels) {
            bend = *levels - 1;
        }

        if (!*n_buckets_ptrs) {
            *n_buckets_ptrs = *levels;
 #if 0
            if (bend == *levels - 1) {
                *n_buckets_ptrs = *levels;
            } else if (bsize >= 256) {
                b_lo_ptrs = bstart;
                spice_assert(bstart);
            }
 #endif
        }

        (*nbuckets)++;
    } while (bend < *levels - 1);
}
