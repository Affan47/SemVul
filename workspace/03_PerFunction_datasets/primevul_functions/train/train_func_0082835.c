image_render_color_thresh(gx_image_enum *penum_orig, const byte *buffer, int data_x,
                          uint w, int h, gx_device * dev)
{
    gx_image_enum *penum = penum_orig;
    image_posture posture = penum->posture;
    int vdi;
    fixed xrun = 0;
    byte *thresh_align;
    byte *devc_contone[GX_DEVICE_COLOR_MAX_COMPONENTS];
    byte *psrc_plane[GX_DEVICE_COLOR_MAX_COMPONENTS];
    byte *devc_contone_gray;
    const byte *psrc = buffer + data_x;
    int dest_width, dest_height, data_length;
    int spp_out = dev->color_info.num_components;
    int position, i, j, k;
    int offset_bits = penum->ht_offset_bits;
    int contone_stride = 0;
    fixed offset;
    int src_size;
    bool flush_buff = false;
    byte *psrc_temp;
    int offset_contone[GX_DEVICE_COLOR_MAX_COMPONENTS];
    int offset_threshold;
    gx_dda_fixed dda_ht;
    int xn, xr;
    int code = 0;
    int spp_cm = 0;
    byte *psrc_cm = NULL, *psrc_cm_start = NULL;
    byte *bufend = NULL;
    int psrc_planestride = w/penum->spp;

    if (h != 0 && penum->line_size != 0) {

        code = image_color_icc_prep(penum, psrc, w, dev, &spp_cm, &psrc_cm,
                                    &psrc_cm_start,  &bufend, true);
        if (code < 0)
            return code;
    } else {
        if (penum->ht_landscape.count == 0 || posture == image_portrait) {
            return 0;
        } else {

            offset_bits = penum->ht_landscape.count;
            penum->ht_offset_bits = offset_bits;
            penum->ht_landscape.offset_set = true;
            flush_buff = true;
        }
    }


    src_size = penum->rect.w;


    dda_ht = (posture == image_portrait) ? penum->dda.pixel0.x : penum->dda.pixel0.y;
    if (penum->dxx > 0)
        dda_translate(dda_ht, -fixed_epsilon);

    switch (posture) {
        case image_portrait:


            xrun = dda_current(dda_ht);
            dest_width = gxht_dda_length(&dda_ht, src_size);
            if (penum->x_extent.x < 0)
                xrun += penum->x_extent.x;
            vdi = penum->hci;
            contone_stride = penum->line_size;
            offset_threshold = (- (((long)(penum->thresh_buffer)) +
                                      penum->ht_offset_bits)) & 15;
            for (k = 0; k < spp_out; k ++) {
                offset_contone[k]   = (- (((long)(penum->line)) +
                                          contone_stride * k +
                                          penum->ht_offset_bits)) & 15;
            }
            data_length = dest_width;
            dest_height = fixed2int_var_rounded(any_abs(penum->y_extent.y));
#ifdef DEBUG

            memset(penum->ht_buffer, 0x00, penum->ht_stride * vdi * spp_out);
#endif
            break;
        case image_landscape:
        default:


            vdi = penum->wci;
            contone_stride = penum->line_size;
            dest_width = fixed2int_var_rounded(any_abs(penum->y_extent.x));

            xrun = dda_current(dda_ht);
            dest_height = gxht_dda_length(&dda_ht, src_size);
            data_length = dest_height;
            offset_threshold = (-(long)(penum->thresh_buffer)) & 15;
            for (k = 0; k < spp_out; k ++) {
                offset_contone[k]   = (- ((long)(penum->line) +
                                          contone_stride * k)) & 15;
            }


            if (penum->ht_landscape.count == 0) {


                penum->ht_landscape.offset_set = true;
                if (penum->ht_landscape.index < 0) {
                    penum->ht_landscape.xstart = penum->xci + vdi - 1;
                    offset_bits = (penum->ht_landscape.xstart % 16) + 1;

                    if (offset_bits <= 0) offset_bits += 16;
                } else {
                    penum->ht_landscape.xstart = penum->xci;

                    offset_bits = 16 - penum->xci % 16;
                    if (offset_bits >= 16) offset_bits -= 16;
                }
                if (offset_bits == 0 || offset_bits == 16) {
                    penum->ht_landscape.offset_set = false;
                    penum->ht_offset_bits = 0;
                } else {
                    penum->ht_offset_bits = offset_bits;
                }
            }
            break;
    }
    if (flush_buff)
        goto flush;


    for (k = 0; k < spp_out; k++) {
        if (posture == image_portrait) {
            devc_contone[k] = penum->line + contone_stride * k +
                              offset_contone[k];
        } else {
            devc_contone[k] = penum->line + offset_contone[k] +
                              LAND_BITS * k * contone_stride;
        }
        psrc_plane[k] = psrc_cm + psrc_planestride * k;
    }
    xr = fixed2int_var_rounded(dda_current(dda_ht));


    switch (spp_out)
    {

        case 1:
            devc_contone_gray = devc_contone[0];
            switch (posture) {

                case image_portrait:
                    if (penum->dst_width > 0) {
                        if (src_size == dest_width) {
                            memcpy(devc_contone_gray, psrc_cm, data_length);
                        } else if (src_size * 2 == dest_width) {
                            psrc_temp = psrc_cm;
                            for (k = 0; k < data_length; k+=2,
                                 devc_contone_gray+=2, psrc_temp++) {
                                *devc_contone_gray =
                                    *(devc_contone_gray+1) = *psrc_temp;
                            }
                        } else {

                        psrc_temp = psrc_cm;
                        for (k=0; k<src_size; k++) {
                            dda_next(dda_ht);
                            xn = fixed2int_var_rounded(dda_current(dda_ht));
                            while (xr < xn) {
                                *devc_contone_gray++ = *psrc_temp;
                                xr++;
                            }
                            psrc_temp++;
                            }
                        }
                    } else {

                        devc_contone_gray += (data_length - 1);
                        psrc_temp = psrc_cm;
                        for (k=0; k<src_size; k++) {
                            dda_next(dda_ht);
                            xn = fixed2int_var_rounded(dda_current(dda_ht));
                            while (xr > xn) {
                                *devc_contone_gray-- = *psrc_temp;
                                xr--;
                            }
                            psrc_temp++;
                            }
                    }
                    break;

                case image_landscape:


                    if (penum->ht_landscape.flipy) {
                        position = penum->ht_landscape.curr_pos +
                                    LAND_BITS * (data_length - 1);
                        psrc_temp = psrc_cm;
                        for (k=0; k<src_size; k++) {
                            dda_next(dda_ht);
                            xn = fixed2int_var_rounded(dda_current(dda_ht));
                            while (xr > xn) {
                                devc_contone_gray[position] = *psrc_temp;
                                position -= LAND_BITS;
                                xr--;
                            }
                            psrc_temp++;
                        }
                    } else {
                        position = penum->ht_landscape.curr_pos;


                        if (src_size == dest_height) {
                            for (k = 0; k < data_length; k++) {
                                devc_contone_gray[position] = psrc_cm[k];
                                position += LAND_BITS;
                            }
                        } else if (src_size*2 == dest_height) {
                            for (k = 0; k < data_length; k+=2) {
                                offset = fixed2int_var_rounded(fixed_half * k);
                                devc_contone_gray[position] =
                                    devc_contone_gray[position + LAND_BITS] =
                                    psrc_cm[offset];
                                position += 2*LAND_BITS;
                            }
                        } else {

                            psrc_temp = psrc_cm;
                            for (k=0; k<src_size; k++) {
                                dda_next(dda_ht);
                                xn = fixed2int_var_rounded(dda_current(dda_ht));
                                while (xr < xn) {
                                    devc_contone_gray[position] = *psrc_temp;
                                    position += LAND_BITS;
                                    xr++;
                                }
                                psrc_temp++;
                            }
                        }
                    }

                    penum->ht_landscape.count += vdi;
                    penum->ht_landscape.widths[penum->ht_landscape.curr_pos] = vdi;
                    penum->ht_landscape.curr_pos += penum->ht_landscape.index;
                    penum->ht_landscape.num_contones++;
                    break;
                default:

                    break;
            }
        break;


        case 4:
            switch (posture) {

                case image_portrait:
                    if (penum->dst_width > 0) {
                        if (src_size == dest_width) {
                            memcpy(devc_contone[0], psrc_plane[0], data_length);
                            memcpy(devc_contone[1], psrc_plane[1], data_length);
                            memcpy(devc_contone[2], psrc_plane[2], data_length);
                            memcpy(devc_contone[3], psrc_plane[3], data_length);
                        } else if (src_size * 2 == dest_width) {
                            for (k = 0; k < data_length; k+=2) {
                                *(devc_contone[0]) = *(devc_contone[0]+1) =
                                    *psrc_plane[0]++;
                                *(devc_contone[1]) = *(devc_contone[1]+1) =
                                    *psrc_plane[1]++;
                                *(devc_contone[2]) = *(devc_contone[2]+1) =
                                    *psrc_plane[2]++;
                                *(devc_contone[3]) = *(devc_contone[3]+1) =
                                    *psrc_plane[3]++;
                                devc_contone[0] += 2;
                                devc_contone[1] += 2;
                                devc_contone[2] += 2;
                                devc_contone[3] += 2;
                            }
                        } else {

                            for (k=0, j=0; k<src_size; k++) {
                                dda_next(dda_ht);
                                xn = fixed2int_var_rounded(dda_current(dda_ht));
                                while (xr < xn) {
                                    *(devc_contone[0])++ = (psrc_plane[0])[j];
                                    *(devc_contone[1])++ = (psrc_plane[1])[j];
                                    *(devc_contone[2])++ = (psrc_plane[2])[j];
                                    *(devc_contone[3])++ = (psrc_plane[3])[j];
                                    xr++;
                                }
                                j++;
                            }
                        }
                    } else {


                        devc_contone[0] += (data_length - 1);
                        devc_contone[1] += (data_length - 1);
                        devc_contone[2] += (data_length - 1);
                        devc_contone[3] += (data_length - 1);
                        for (k=0, j=0; k<src_size; k++) {
                            dda_next(dda_ht);
                            xn = fixed2int_var_rounded(dda_current(dda_ht));
                            while (xr > xn) {
                                *(devc_contone[0])-- = (psrc_plane[0])[j];
                                *(devc_contone[1])-- = (psrc_plane[1])[j];
                                *(devc_contone[2])-- = (psrc_plane[2])[j];
                                *(devc_contone[3])-- = (psrc_plane[3])[j];
                                xr--;
                            }
                            j++;
                        }
                    }
                    break;

                case image_landscape:


                    if (penum->ht_landscape.flipy) {
                        position = penum->ht_landscape.curr_pos +
                                    LAND_BITS * (data_length - 1);

                        for (k=0, i=0; k<src_size; k++) {
                            dda_next(dda_ht);
                            xn = fixed2int_var_rounded(dda_current(dda_ht));
                            while (xr > xn) {
                                for (j = 0; j < spp_out; j++) {
                                    *(devc_contone[j] + position) = (psrc_plane[j])[i];
                                    position -= LAND_BITS;
                                }
                                xr--;
                            }
                            i++;
                        }
                    } else {
                        position = penum->ht_landscape.curr_pos;


                        for (k = 0; k < spp_out; k++) {
                            devc_contone[k] = devc_contone[k] + position;
                        }
                        if (src_size == dest_height) {
                            for (k = 0; k < data_length; k++) {

                                for (j = 0; j < spp_out; j++) {
                                    *(devc_contone[j]) = (psrc_plane[j])[k];
                                    devc_contone[j] += LAND_BITS;
                                }
                            }
                        } else if (src_size*2 == dest_height) {
                            for (k = 0; k < data_length; k+=2) {
                                offset = fixed2int_var_rounded(fixed_half * k);

                                for (j = 0; j < spp_out; j++) {
                                    *(devc_contone[j]) =
                                      *(devc_contone[j] + LAND_BITS) =
                                      (psrc_plane[j])[offset];
                                    devc_contone[j] += 2 * LAND_BITS;
                                }
                            }
                        } else {

                            for (k=0, i=0; k<src_size; k++) {
                                dda_next(dda_ht);
                                xn = fixed2int_var_rounded(dda_current(dda_ht));
                                while (xr > xn) {
                                    for (j = 0; j < spp_out; j++) {
                                        *(devc_contone[j] + position) = (psrc_plane[j])[i];
                                        position -= LAND_BITS;
                                    }
                                    xr--;
                                }
                                i++;
                            }
                        }
                    }

                    penum->ht_landscape.count += vdi;
                    penum->ht_landscape.widths[penum->ht_landscape.curr_pos] = vdi;
                    penum->ht_landscape.curr_pos += penum->ht_landscape.index;
                    penum->ht_landscape.num_contones++;
                    break;
                default:

                    break;
            }
        break;
        default:

        break;
    }


flush:
    thresh_align = penum->thresh_buffer + offset_threshold;
    code = gxht_thresh_planes(penum, xrun, dest_width, dest_height,
                              thresh_align, dev, offset_contone,
                              contone_stride);

    if (psrc_cm_start != NULL) {
        gs_free_object(penum->pgs->memory, (byte *)psrc_cm_start,
                       "image_render_color_thresh");
    }
    return code;
}
