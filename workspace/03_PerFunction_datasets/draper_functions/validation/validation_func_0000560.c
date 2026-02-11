kmclipm_priv_paste_ifu_images(const cpl_image *ifu_img,
                                    cpl_image **out_img,
                                    const int x_pos,
                                    const int y_pos)
{
    int             x           = 0,
                    y           = 0,
                    c           = 0,
                    ifu_x_size  = 0,
                    ifu_y_size  = 0,
                    out_x_size  = 0,
                    out_y_size  = 0;

    const float     *v          = NULL;

    float           max_val     = 0;

    KMCLIPM_TRY
    {

        KMCLIPM_TRY_CHECK_AUTOMSG(ifu_img != NULL,
            CPL_ERROR_NULL_INPUT);

        KMCLIPM_TRY_CHECK_AUTOMSG(*out_img != NULL,
            CPL_ERROR_NULL_INPUT);

        ifu_x_size = cpl_image_get_size_x(ifu_img);
        ifu_y_size = cpl_image_get_size_y(ifu_img);
        out_x_size = cpl_image_get_size_x(*out_img);
        out_y_size = cpl_image_get_size_y(*out_img);


        KMCLIPM_TRY_EXIT_IFN(
            v = cpl_image_get_data_float_const(ifu_img));
        KMCLIPM_TRY_CHECK_ERROR_STATE();

        for (y = 0; y < ifu_y_size; y++) {
            for (x = 0; x < ifu_x_size; x++) {
                if ((x_pos + x > 0) && (x_pos + x <= out_x_size) &&
                    (y_pos + y > 0) && (y_pos + y <= out_y_size))
                {
                    KMCLIPM_TRY_EXIT_IFN(
                        cpl_image_set(*out_img, x_pos + x,
                                      y_pos + y, v[c]) == CPL_ERROR_NONE);
                }
                if (v[c] > max_val)
                    max_val = v[c];
                c++;
            }
        }
    }
    KMCLIPM_CATCH
    {
        max_val = -1.0;
    }

    return max_val;
}
