gxht_thresh_planes(gx_image_enum *penum, fixed xrun,
                   int dest_width, int dest_height,
                   byte *thresh_align, gx_device * dev, int offset_contone[],
                   int contone_stride)
{
    int thresh_width, thresh_height, dx;
    int left_rem_end, left_width, vdi;
    int num_full_tiles, right_tile_width;
    int k, jj, dy, j;
    byte *thresh_tile;
    int position;
    bool replicate_tile;
    image_posture posture = penum->posture;
    const int y_pos = penum->yci;
    int width = 0;
    byte *ptr_out, *row_ptr, *ptr_out_temp;
    byte *threshold;
    int init_tile, in_row_offset, ii, num_tiles, tile_remainder;
    int offset_bits = penum->ht_offset_bits;
    byte *halftone;
    int dithered_stride = penum->ht_stride;
    bool is_planar_dev = dev->is_planar;
    gx_color_index dev_white = gx_device_white(dev);
    gx_color_index dev_black = gx_device_black(dev);
    int spp_out = dev->color_info.num_components;
    byte *contone_align = NULL;


    switch (posture) {
        case image_portrait:
            vdi = penum->hci;


            for (j = 0; j < spp_out; j++) {
                bool threshold_inverted = penum->pgs->dev_ht->components[j].corder.threshold_inverted;

                thresh_width = penum->pgs->dev_ht->components[j].corder.width;
                thresh_height = penum->pgs->dev_ht->components[j].corder.full_height;
                halftone = penum->ht_buffer + j * vdi * dithered_stride;

                dx = (fixed2int_var_rounded(xrun) + penum->pgs->screen_phase[0].x) % thresh_width;

                left_rem_end = min(dx + dest_width, thresh_width);

                left_width = left_rem_end - dx;

                num_full_tiles =
                    (int)fastfloor((dest_width - left_width)/ (float) thresh_width);

                right_tile_width = dest_width -  num_full_tiles * thresh_width -
                                   left_width;

                threshold = penum->pgs->dev_ht->components[j].corder.threshold;

                contone_align = penum->line + contone_stride * j +
                                offset_contone[j];
                for (k = 0; k < vdi; k++) {

                    dy = (penum->yci + k + penum->dev->band_offset_y) % thresh_height;
                    if (dy < 0)
                        dy += thresh_height;
                    thresh_tile = threshold + thresh_width * dy;


                    position = contone_stride * k;

                    fill_threshold_buffer(&(thresh_align[position]),
                                           thresh_tile, thresh_width, dx, left_width,
                                           num_full_tiles, right_tile_width);
                }

                if (offset_bits > dest_width)
                    offset_bits = dest_width;

                if (threshold_inverted ||
                    (dev->color_info.polarity == GX_CINFO_POLARITY_SUBTRACTIVE && is_planar_dev)) {
                    gx_ht_threshold_row_bit_sub(contone_align, thresh_align, contone_stride,
                                      halftone, dithered_stride, dest_width, vdi,
                                      offset_bits);
                } else {
                    gx_ht_threshold_row_bit(contone_align, thresh_align, contone_stride,
                          halftone, dithered_stride, dest_width, vdi,
                          offset_bits);
                }
            }


            if (offset_bits > 0) {
                int x_pos = fixed2int_var_rounded(xrun);
                if (!is_planar_dev) {
                    (*dev_proc(dev, copy_mono)) (dev, penum->ht_buffer, 0, dithered_stride,
                                                 gx_no_bitmap_id, x_pos, y_pos,
                                                 offset_bits, vdi, dev_white,
                                                 dev_black);
                } else {
                    (*dev_proc(dev, copy_planes)) (dev, penum->ht_buffer, 0, dithered_stride,
                                                 gx_no_bitmap_id, x_pos, y_pos,
                                                 offset_bits, vdi, vdi);
                }
            }
            if ((dest_width - offset_bits) > 0 ) {

                int curr_width = dest_width - offset_bits;
                int x_pos = fixed2int_var_rounded(xrun) + offset_bits;

                int xoffs = offset_bits > 0 ? 16 : 0;

                if (!is_planar_dev) {
                    (*dev_proc(dev, copy_mono)) (dev, penum->ht_buffer, xoffs, dithered_stride,
                                                 gx_no_bitmap_id, x_pos, y_pos,
                                                 curr_width, vdi, dev_white,
                                                 dev_black);
                } else {
                    (*dev_proc(dev, copy_planes)) (dev, penum->ht_buffer, xoffs, dithered_stride,
                                                 gx_no_bitmap_id, x_pos, y_pos,
                                                 curr_width, vdi, vdi);
                }
            }

            break;
        case image_landscape:


            vdi = penum->wci;


            while ( (penum->ht_landscape.count >= LAND_BITS ||
                   ((penum->ht_landscape.count >= offset_bits) &&
                    penum->ht_landscape.offset_set))) {


                for (j = 0; j < spp_out; j++) {
                    halftone = penum->ht_buffer +
                                   j * penum->ht_plane_height * (LAND_BITS>>3);
                    thresh_width = penum->pgs->dev_ht->components[j].corder.width;
                    thresh_height =
                          penum->pgs->dev_ht->components[j].corder.full_height;

                    threshold = penum->pgs->dev_ht->components[j].corder.threshold;

                    contone_align = penum->line + offset_contone[j] +
                                      LAND_BITS * j * contone_stride;
                    if (penum->ht_landscape.offset_set) {
                        width = offset_bits;
                    } else {
                        width = LAND_BITS;
                    }
                    if (penum->y_extent.x < 0) {
                        dx = penum->ht_landscape.xstart - width + 1;
                    } else {
                        dx = penum->ht_landscape.xstart;
                    }
                    dx = (dx + penum->pgs->screen_phase[0].x) % thresh_width;
                    dy = (penum->ht_landscape.y_pos +
                              penum->dev->band_offset_y) % thresh_height;
                    if (dy < 0)
                        dy += thresh_height;

                    left_rem_end = min(dx + LAND_BITS, thresh_width);
                    left_width = left_rem_end - dx;

                    num_full_tiles = (LAND_BITS - left_width) / thresh_width;

                    right_tile_width =
                        LAND_BITS - num_full_tiles * thresh_width - left_width;

                    ptr_out = thresh_align;


                    if (dest_height <= 2 * thresh_height) {
                        init_tile = dest_height;
                        replicate_tile = false;
                    } else {
                        init_tile = thresh_height;
                        replicate_tile = true;
                    }
                    for (jj = 0; jj < init_tile; jj++) {
                        in_row_offset = (jj + dy) % thresh_height;
                        row_ptr = threshold + in_row_offset * thresh_width;
                        ptr_out_temp = ptr_out;

                        memcpy(ptr_out_temp, row_ptr + dx, left_width);
                        ptr_out_temp += left_width;

                        for (ii = 0; ii < num_full_tiles; ii++) {
                            memcpy(ptr_out_temp, row_ptr, thresh_width);
                            ptr_out_temp += thresh_width;
                        }

                        memcpy(ptr_out_temp, row_ptr, right_tile_width);
                        ptr_out += LAND_BITS;
                    }
                    if (replicate_tile) {

                        num_tiles =
                            (int)fastfloor((float) (dest_height - thresh_height)/ (float) thresh_height);
                        tile_remainder = dest_height - (num_tiles + 1) * thresh_height;
                        for (jj = 0; jj < num_tiles; jj ++) {
                            memcpy(ptr_out, thresh_align, LAND_BITS * thresh_height);
                            ptr_out += LAND_BITS * thresh_height;
                        }

                        memcpy(ptr_out, thresh_align, LAND_BITS * tile_remainder);
                    }

                    if (dev->color_info.polarity == GX_CINFO_POLARITY_SUBTRACTIVE
                        && is_planar_dev) {
                        gx_ht_threshold_landscape_sub(contone_align, thresh_align,
                                            &(penum->ht_landscape), halftone, dest_height);
                    } else {
                        gx_ht_threshold_landscape(contone_align, thresh_align,
                                            &(penum->ht_landscape), halftone, dest_height);
                    }


                    if (width != penum->ht_landscape.count) {

                        move_landscape_buffer(&(penum->ht_landscape),
                                              contone_align, dest_height);
                    }
                }

                if (penum->ht_landscape.index < 0) {
                    if (!is_planar_dev) {
                        (*dev_proc(dev, copy_mono))
                                       (dev, penum->ht_buffer, 0, LAND_BITS>>3,
                                        gx_no_bitmap_id,
                                        penum->ht_landscape.xstart - width + 1,
                                        penum->ht_landscape.y_pos,
                                        width, dest_height,
                                        dev_white, dev_black);
                    } else {
                        (*dev_proc(dev, copy_planes))
                                       (dev, penum->ht_buffer, 0, LAND_BITS>>3,
                                        gx_no_bitmap_id,
                                        penum->ht_landscape.xstart - width + 1,
                                        penum->ht_landscape.y_pos,
                                        width, dest_height,
                                        penum->ht_plane_height);
                    }
                } else {
                    if (!is_planar_dev) {
                        (*dev_proc(dev, copy_mono)) (dev, penum->ht_buffer, 0, LAND_BITS>>3,
                                                     gx_no_bitmap_id,
                                                     penum->ht_landscape.xstart,
                                                     penum->ht_landscape.y_pos,
                                                     width, dest_height,
                                                     dev_white, dev_black);
                    } else {
                        (*dev_proc(dev, copy_planes)) (dev, penum->ht_buffer, 0, LAND_BITS>>3,
                                                     gx_no_bitmap_id,
                                                     penum->ht_landscape.xstart,
                                                     penum->ht_landscape.y_pos,
                                                     width, dest_height,
                                                     penum->ht_plane_height);
                    }
                }
                penum->ht_landscape.offset_set = false;
                if (width != penum->ht_landscape.count) {
                    reset_landscape_buffer(&(penum->ht_landscape),
                                           contone_align, dest_height,
                                           width);
                } else {

                    penum->ht_landscape.count = 0;
                    if (penum->ht_landscape.index < 0) {

                        penum->ht_landscape.curr_pos = LAND_BITS-1;
                    } else {

                        penum->ht_landscape.curr_pos = 0;
                    }
                    penum->ht_landscape.num_contones = 0;
                    memset(&(penum->ht_landscape.widths[0]), 0, sizeof(int)*LAND_BITS);
                }
            }
            break;
        default:
            return gs_rethrow(-1, "Invalid orientation for thresholding");
    }
    return 0;
}
