_giraffe_rebin_setup_grating(GiImage *extspectra, GiTable *grating,
                             GiTable *wlsolution)
{

    cxint status = 0;

    cpl_propertylist *properties = NULL;

    cpl_matrix *setup = NULL;

    GiGrat *grating_data = _giraffe_grating_new();


    status = _giraffe_grating_setup(grating, extspectra, grating_data);

    if (status != 0) {
        _giraffe_grating_delete(grating_data);
        return NULL;
    }


    properties = giraffe_table_get_properties(wlsolution);

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMFCOLL)) {
        grating_data->fcoll = cpl_propertylist_get_double(properties,
                                                          GIALIAS_WSOL_OMFCOLL);
    }

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMGCAM)) {
        grating_data->gcam = cpl_propertylist_get_double(properties,
                                                         GIALIAS_WSOL_OMGCAM);
    }

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMGTHETA)) {
        grating_data->theta = cpl_propertylist_get_double(properties,
                                                          GIALIAS_WSOL_OMGTHETA);
    }

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMSDX)) {
        grating_data->slitdx = cpl_propertylist_get_double(properties,
                                                           GIALIAS_WSOL_OMSDX);
    }

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMSDY)) {
        grating_data->slitdy = cpl_propertylist_get_double(properties,
                                                           GIALIAS_WSOL_OMSDY);
    }

    if (cpl_propertylist_has(properties, GIALIAS_WSOL_OMSPHI)) {
        grating_data->slitphi = cpl_propertylist_get_double(properties,
                                                            GIALIAS_WSOL_OMSPHI);
    }


    setup = cpl_matrix_new(7, 1);

    cpl_matrix_set(setup, 0, 0, grating_data->theta);
    cpl_matrix_set(setup, 1, 0, grating_data->order);
    cpl_matrix_set(setup, 2, 0, grating_data->wlenmin / GI_MM_TO_NM);
    cpl_matrix_set(setup, 3, 0, grating_data->wlen0 / GI_MM_TO_NM);
    cpl_matrix_set(setup, 4, 0, grating_data->wlenmax / GI_MM_TO_NM);
    cpl_matrix_set(setup, 5, 0, grating_data->resol);
    cpl_matrix_set(setup, 6, 0, grating_data->space);

    _giraffe_grating_delete(grating_data);
    grating_data = NULL;

    return setup;

}
