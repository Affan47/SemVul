image1_setup(i_ctx_t * i_ctx_p, bool has_alpha)
{
    os_ptr          op = osp;
    gs_image_t      image;
    image_params    ip;
    int             code;
    gs_color_space *csp = gs_currentcolorspace(igs);


    if (gs_currentcpsimode(imemory) && gs_color_space_num_components(csp) < 1) {
       gs_color_space *bsp = csp->base_space;
       if (bsp)
         csp = bsp;
    }

    gs_image_t_init(&image, csp);
    code = pixel_image_params( i_ctx_p,
                               op,
                               (gs_pixel_image_t *)&image,
                               &ip,
                               (level2_enabled ? 16 : 8),
                               has_alpha, csp);
    if (code < 0)
        return code;

    image.Alpha = (has_alpha ? gs_image_alpha_last : gs_image_alpha_none);


    if (image.Width == 1 && image.Height > 1 && image.BitsPerComponent == 8 &&
        image.ImageMatrix.xy == 0.0 && image.ImageMatrix.yx == 0.0 &&
        image.ImageMatrix.tx == 0.0) {
        float ftmp;
        int   itemp;

        itemp = image.Width;
        image.Width = image.Height;
        image.Height = itemp;

        image.ImageMatrix.xy = image.ImageMatrix.xx;
        image.ImageMatrix.yx = image.ImageMatrix.yy;
        image.ImageMatrix.xx = 0.0;
        image.ImageMatrix.yy = 0.0;
        ftmp = image.ImageMatrix.tx;
        image.ImageMatrix.tx = image.ImageMatrix.ty;
        image.ImageMatrix.ty = ftmp;
    }
    return zimage_setup( i_ctx_p,
                         (gs_pixel_image_t *)&image,
                         &ip.DataSource[0],
                         image.CombineWithColor,
                         1 );
}
