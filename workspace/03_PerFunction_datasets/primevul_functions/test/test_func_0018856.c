gx_ht_threshold_landscape_sub(byte *contone_align, byte *thresh_align,
                    ht_landscape_info_t *ht_landscape, byte *halftone,
                    int data_length)
{
    __align16 byte contone[LAND_BITS];
    int position_start, position, curr_position;
    int *widths = &(ht_landscape->widths[0]);
    int local_widths[LAND_BITS];
    int num_contone = ht_landscape->num_contones;
    int k, j, w, contone_out_posit;
    byte *contone_ptr, *thresh_ptr, *halftone_ptr;
#ifdef PACIFY_VALGRIND
    int extra = 0;
#endif


    if (ht_landscape->index > 0) {
        position = position_start = 0;
    } else {
        position = position_start = ht_landscape->curr_pos + 1;
    }
    thresh_ptr = thresh_align;
    halftone_ptr = halftone;


    k = 0;
    for (j = 0; j < num_contone; j++)
        k += (local_widths[j] = widths[position_start+j]);
    if (k > LAND_BITS) {
        if (ht_landscape->index > 0) {
            local_widths[num_contone-1] -= k-LAND_BITS;
        } else {
            local_widths[0] -= k-LAND_BITS;
        }
    }
#ifdef PACIFY_VALGRIND
    if (k < LAND_BITS) {
        extra = LAND_BITS - k;
    }
#endif
    for (k = data_length; k > 0; k--) {
        contone_ptr = &(contone_align[position]);
        curr_position = 0;
        contone_out_posit = 0;
        for (j = num_contone; j > 0; j--) {
            byte c = *contone_ptr;


            w = local_widths[curr_position];
            do {
                ((volatile byte *)contone)[contone_out_posit] = c;
                contone_out_posit++;
            } while (--w);
#ifdef PACIFY_VALGRIND
            if (extra)
                memset(contone+contone_out_posit, 0, extra);
#endif
            curr_position++;
            contone_ptr++;
        }


        contone_ptr = &contone[0];
#if LAND_BITS > 16
        j = LAND_BITS;
        do {
#endif
#ifdef HAVE_SSE2
            threshold_16_SSE(thresh_ptr, contone_ptr, halftone_ptr);
#else
            threshold_16_bit(thresh_ptr, contone_ptr, halftone_ptr);
#endif
            thresh_ptr += 16;
            position += 16;
            halftone_ptr += 2;
            contone_ptr += 16;
#if LAND_BITS > 16
            j -= 16;
        } while (j > 0);
#endif
    }
}
