kmo_copy_vector_F3I_z(cpl_imagelist *data,
                                      int x,
                                      int y,
                                      int z1, int z2)
{
    kmclipm_vector  *vec            = NULL;
    cpl_image       *img            = NULL;
    double          *pvecd          = NULL,
                    *pvecm          = NULL,
                    tmp             = 0;
    int             i               = 0,
                    j               = 0,
                    rej             = 0;

    KMO_TRY
    {
        KMO_TRY_ASSURE(data != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_ASSURE(z1 <= z2,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "z1 > z2! z1 = %d, z2 = %d", z1, z2);

        KMO_TRY_ASSURE((cpl_imagelist_get_size(data) >= z1) &&
                       (z1 > 0),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "z1 < 1 or z1 > size of cube! z1 = %d", z1);

        KMO_TRY_ASSURE((cpl_imagelist_get_size(data) >= z2) &&
                       (z2 > 0),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "z2 < 1 or z2 > size of cube! z2 = %d", z2);

        KMO_TRY_EXIT_IF_NULL(
            vec = kmclipm_vector_new(z2 - z1 + 1));
        KMO_TRY_EXIT_IF_NULL(
            pvecd = cpl_vector_get_data(vec->data));
        KMO_TRY_EXIT_IF_NULL(
            pvecm = cpl_vector_get_data(vec->mask));

        KMO_TRY_EXIT_IF_NULL(
            img = cpl_imagelist_get(data, 0));

        KMO_TRY_ASSURE((cpl_image_get_size_y(img) >= y) &&
                       (y > 0),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "y < 1 or y > size of cube! y = %d", y);

        KMO_TRY_ASSURE((cpl_image_get_size_x(img) >= x) &&
                       (x > 0),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "x < 1 or x > size of cube! x = %d", x);

        for (i = z1 - 1; i < z2; i++) {
            KMO_TRY_EXIT_IF_NULL(
                img = cpl_imagelist_get(data, i));

            tmp = cpl_image_get(img, x, y, &rej);
            if (rej == 1) {
                pvecm[j++] = 0;
            } else {
                pvecd[j++] = tmp;
            }
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        kmclipm_vector_delete(vec); vec = NULL;
    }

    return vec;
}
