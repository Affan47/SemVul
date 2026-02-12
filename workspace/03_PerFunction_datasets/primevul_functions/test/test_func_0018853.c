gxht_thresh_image_init(gx_image_enum *penum)
{
    int code = 0;
    fixed ox;
    int temp;
    int dev_width, max_height;
    int spp_out;
    int k;
    gx_ht_order *d_order;
    gx_dda_fixed dda_ht;

    if (gx_device_must_halftone(penum->dev)) {
        if (penum->pgs != NULL && penum->pgs->dev_ht != NULL) {
            for (k = 0; k < penum->pgs->dev_ht->num_comp; k++) {
                d_order = &(penum->pgs->dev_ht->components[k].corder);
                code = gx_ht_construct_threshold(d_order, penum->dev,
                                                 penum->pgs, k);
                if (code < 0 ) {
                    return gs_rethrow(code, "threshold creation failed");
                }
            }
        } else {
            return -1;
        }
    }
    spp_out = penum->dev->color_info.num_components;

    penum->dxx = float2fixed(penum->matrix.xx + fixed2float(fixed_epsilon) / 2);


    if (penum->posture == image_landscape) {
        int col_length = fixed2int_var_rounded(any_abs(penum->x_extent.y));
        dda_ht = penum->dda.pixel0.y;
        if (penum->dxx > 0)
            dda_translate(dda_ht, -fixed_epsilon);

        ox = dda_current(penum->dda.pixel0.x);
        temp = gxht_dda_length(&dda_ht, penum->rect.w);
        if (col_length < temp)
            col_length = temp;
        temp = (col_length + LAND_BITS)/LAND_BITS;

        penum->line_size = bitmap_raster((temp * LAND_BITS) * 8);

        penum->line = gs_alloc_bytes(penum->memory,
                                     LAND_BITS * penum->line_size * spp_out + 16,
                                     "gxht_thresh");

        penum->thresh_buffer = gs_alloc_bytes(penum->memory,
                                           penum->line_size * LAND_BITS + 16,
                                           "gxht_thresh");

        penum->ht_buffer =
                        gs_alloc_bytes(penum->memory,
                           penum->line_size * (LAND_BITS>>3) * spp_out,
                           "gxht_thresh");
        penum->ht_plane_height = penum->line_size;
        penum->ht_stride = penum->line_size;
        if (penum->line == NULL || penum->thresh_buffer == NULL
                    || penum->ht_buffer == NULL)
            return -1;
        penum->ht_landscape.count = 0;
        penum->ht_landscape.num_contones = 0;
        if (penum->y_extent.x < 0) {

            penum->ht_landscape.curr_pos = LAND_BITS-1;
            penum->ht_landscape.index = -1;
        } else {

            penum->ht_landscape.curr_pos = 0;
            penum->ht_landscape.index = 1;
        }
        if (penum->x_extent.y < 0) {
            penum->ht_landscape.flipy = true;
            penum->ht_landscape.y_pos =
                fixed2int_pixround_perfect(dda_current(penum->dda.pixel0.y) + penum->x_extent.y);
        } else {
            penum->ht_landscape.flipy = false;
            penum->ht_landscape.y_pos =
                fixed2int_pixround_perfect(dda_current(penum->dda.pixel0.y));
        }
        memset(&(penum->ht_landscape.widths[0]), 0, sizeof(int)*LAND_BITS);
        penum->ht_landscape.offset_set = false;
        penum->ht_offset_bits = 0;
        if (code >= 0) {
#if defined(DEBUG) || defined(PACIFY_VALGRIND)
            memset(penum->line, 0, LAND_BITS * penum->line_size * spp_out + 16);
            memset(penum->ht_buffer, 0, penum->line_size * (LAND_BITS>>3) * spp_out);
            memset(penum->thresh_buffer, 0, LAND_BITS * penum->line_size + 16);
#endif
        }
    } else {


        dda_ht = penum->dda.pixel0.x;
        if (penum->dxx > 0)
            dda_translate(dda_ht, -fixed_epsilon);

        memset(&(penum->ht_landscape), 0, sizeof(ht_landscape_info_t));
        ox = dda_current(dda_ht);
        dev_width = gxht_dda_length(&dda_ht, penum->rect.w);


        penum->ht_offset_bits = (-fixed2int_var_rounded(ox)) & (bitmap_raster(1) - 1);
        if (penum->ht_offset_bits > 0) {
            penum->ht_stride = bitmap_raster((7 + (dev_width + 4)) + (ARCH_SIZEOF_LONG * 8));
        } else {
            penum->ht_stride = bitmap_raster((7 + (dev_width + 2)) + (ARCH_SIZEOF_LONG * 8));
        }


        max_height = (int) ceil(fixed2float(any_abs(penum->dst_height)) /
                                            (float) penum->Height);
        if (max_height <= 0)
            return -1;
        if (penum->ht_stride * spp_out > max_int / max_height)
            return -1;

        penum->ht_buffer =
                        gs_alloc_bytes(penum->memory,
                           penum->ht_stride * max_height * spp_out,
                           "gxht_thresh");
        penum->ht_plane_height = penum->ht_stride * max_height;


        temp = (int) ceil((float) ((dev_width + 15.0) + 15.0)/16.0);
        penum->line_size = bitmap_raster(temp * 16 * 8);
        if (penum->line_size > max_int / max_height) {
            gs_free_object(penum->memory, penum->ht_buffer, "gxht_thresh");
            penum->ht_buffer = NULL;
            return -1;
        }
        penum->line = gs_alloc_bytes(penum->memory, penum->line_size * spp_out,
                                     "gxht_thresh");
        penum->thresh_buffer = gs_alloc_bytes(penum->memory,
                                              penum->line_size * max_height,
                                              "gxht_thresh");
        if (penum->line == NULL || penum->thresh_buffer == NULL ||
            penum->ht_buffer == NULL) {
            return -1;
        } else {
#if defined(DEBUG) || defined(PACIFY_VALGRIND)
            memset(penum->line, 0, penum->line_size * spp_out);
            memset(penum->ht_buffer, 0, penum->ht_stride * max_height * spp_out);
            memset(penum->thresh_buffer, 0, penum->line_size * max_height);
#endif
        }
    }
    return code;
}
