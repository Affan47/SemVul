p3d_prepare_wdata(ExtractControls *controls, ExtractArgs *args)
{
    gint i;

    if (controls->brick == NULL) {

        return;
    }


    for (i=0; i<3; i++) {
        controls->wpx[i] = controls->px[i];
        controls->wpy[i] = controls->py[i];
        controls->wpz[i] = controls->pz[i];
    }

    for (i=3; i<controls->nps; i++)
    {
        controls->wpx[i] = controls->px[i];
        controls->wpy[i] = controls->py[i];
        controls->wpz[i] = controls->pz[i]*args->zscale/100.0;
    }

}
