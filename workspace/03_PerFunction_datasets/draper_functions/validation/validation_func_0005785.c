do_cut(CutArgs *args)
{
    gint i, j, k, ndata, nndata, cstart, cend;
    GwyContainer *data;
    GwyGraphModel *ngmodel, *gmodel;
    GwyGraphCurveModel *gcmodel, *ngcmodel;
    const gdouble *xdata, *ydata;
    gdouble *nxdata, *nydata;

    gmodel = gwy_graph_get_model(args->parent_graph);
    ngmodel = gwy_graph_model_new_alike(gmodel);

    if (args->is_all) {
        cstart = 0;
        cend = gwy_graph_model_get_n_curves(gmodel);
    }
    else {
        cstart = args->curve;
        cend = args->curve + 1;
    }

    for (k = cstart; k < cend; k++) {
        gcmodel = gwy_graph_model_get_curve(gmodel, k);
        ngcmodel = gwy_graph_curve_model_duplicate(gcmodel);

        xdata = gwy_graph_curve_model_get_xdata(gcmodel);
        ydata = gwy_graph_curve_model_get_ydata(gcmodel);
        ndata = gwy_graph_curve_model_get_ndata(gcmodel);


        nndata = 0;
        for (i = 0; i < ndata; i++) {
            if (xdata[i] >= args->from && xdata[i] < args->to)
                nndata++;
        }

        if (nndata == 0) {
            g_object_unref(ngcmodel);
            continue;
        }
        nxdata = g_new(gdouble, nndata);
        nydata = g_new(gdouble, nndata);

        j = 0;
        for (i = 0; i < ndata; i++) {
            if (xdata[i]>=args->from && xdata[i]<args->to) {
                nxdata[j] = xdata[i];
                nydata[j] = ydata[i];
                j++;
            }
        }
        gwy_graph_curve_model_set_data(ngcmodel, nxdata, nydata, nndata);
        g_free(nxdata);
        g_free(nydata);

        gwy_graph_model_add_curve(ngmodel, ngcmodel);
        g_object_unref(ngcmodel);
    }

    gwy_app_data_browser_get_current(GWY_APP_CONTAINER, &data, NULL);
    gwy_app_data_browser_add_graph_model(ngmodel, data, TRUE);

    g_object_unref(ngmodel);
}
