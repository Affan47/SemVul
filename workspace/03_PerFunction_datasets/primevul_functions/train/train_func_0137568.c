image_color_icc_prep(gx_image_enum *penum_orig, const byte *psrc, uint w,
                     gx_device *dev, int *spp_cm_out, byte **psrc_cm,
                     byte **psrc_cm_start, byte **bufend, bool planar_out)
{
    const gx_image_enum *const penum = penum_orig;
    const gs_gstate *pgs = penum->pgs;
    bool need_decode = penum->icc_setup.need_decode;
    gsicc_bufferdesc_t input_buff_desc;
    gsicc_bufferdesc_t output_buff_desc;
    int num_pixels, spp_cm;
    int spp = penum->spp;
    bool force_planar = false;
    int num_des_comps;
    int code;
    cmm_dev_profile_t *dev_profile;
    byte *psrc_decode;
    const byte *planar_src;
    byte *planar_des;
    int j, k;
    int width;

    code = dev_proc(dev, get_profile)(dev, &dev_profile);
    if (code < 0) return code;
    num_des_comps = gsicc_get_device_profile_comps(dev_profile);
    if (penum->icc_link == NULL) {
        return gs_rethrow(-1, "ICC Link not created during image render color");
    }


    if (num_des_comps != 1 && planar_out == true) {
        force_planar = true;
    }
    if (penum->icc_link->is_identity && !need_decode && !force_planar) {

        *psrc_cm = (unsigned char *) psrc;
        spp_cm = spp;
        *bufend = *psrc_cm + w;
        *psrc_cm_start = NULL;
    } else {
        spp_cm = num_des_comps;


        *psrc_cm_start = gs_alloc_bytes(pgs->memory,  w * spp_cm/spp + 64,
                                  "image_color_icc_prep");
        *psrc_cm = *psrc_cm_start + ((32 - (intptr_t)(*psrc_cm_start)) & 31);
        *bufend = *psrc_cm +  w * spp_cm/spp;
        if (penum->icc_link->is_identity) {
            if (!force_planar) {

                decode_row(penum, psrc, spp, *psrc_cm, *bufend);
            } else {


                if (need_decode) {

                    psrc_decode = gs_alloc_bytes(pgs->memory,  w,
                                                  "image_color_icc_prep");
                    if (!penum->use_cie_range) {
                        decode_row(penum, psrc, spp, psrc_decode, psrc_decode+w);
                    } else {

                        decode_row_cie(penum, psrc, spp, psrc_decode,
                                        psrc_decode + w, get_cie_range(penum->pcs));
                    }
                    planar_src = psrc_decode;
                } else {
                    psrc_decode = NULL;
                    planar_src = psrc;
                }

                width = w/spp;
                planar_des = *psrc_cm;
                for (k = 0; k < width; k++) {
                    for (j = 0; j < spp; j++) {
                        *(planar_des + j * width) = *planar_src++;
                    }
                    planar_des++;
                }

                if (psrc_decode != NULL) {
                    gs_free_object(pgs->memory, (byte *) psrc_decode,
                                   "image_render_color_icc");
                }
            }
        } else {

            num_pixels = w/spp;
            gsicc_init_buffer(&input_buff_desc, spp, 1,
                          false, false, false, 0, w,
                          1, num_pixels);
            if (!force_planar) {
                gsicc_init_buffer(&output_buff_desc, spp_cm, 1,
                              false, false, false, 0, num_pixels * spp_cm,
                              1, num_pixels);
            } else {
                gsicc_init_buffer(&output_buff_desc, spp_cm, 1,
                              false, false, true, w/spp, w/spp,
                              1, num_pixels);
            }


            if (need_decode) {

                psrc_decode = gs_alloc_bytes(pgs->memory, w,
                                              "image_color_icc_prep");
                if (!penum->use_cie_range) {
                    decode_row(penum, psrc, spp, psrc_decode, psrc_decode+w);
                } else {

                    decode_row_cie(penum, psrc, spp, psrc_decode,
                                    psrc_decode+w, get_cie_range(penum->pcs));
                }
                (penum->icc_link->procs.map_buffer)(dev, penum->icc_link,
                                                    &input_buff_desc,
                                                    &output_buff_desc,
                                                    (void*) psrc_decode,
                                                    (void*) *psrc_cm);
                gs_free_object(pgs->memory, psrc_decode, "image_color_icc_prep");
            } else {

                (penum->icc_link->procs.map_buffer)(dev, penum->icc_link,
                                                    &input_buff_desc,
                                                    &output_buff_desc,
                                                    (void*) psrc,
                                                    (void*) *psrc_cm);
            }
        }
    }
    *spp_cm_out = spp_cm;
    return 0;
}
