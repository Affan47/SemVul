kmo_init_fits_sub_desc(sub_fits_desc *desc)
{
    KMO_TRY
    {
        KMO_TRY_ASSURE(desc != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "No input data is provided!");

        desc->ext_nr     = -1;
        desc->valid_data = -1;
        desc->is_noise   = -1;
        desc->is_badpix  = -1;
        desc->device_nr  = -1;

    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
    }
}
