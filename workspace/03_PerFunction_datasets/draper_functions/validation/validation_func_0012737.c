GCol_ShowTexts(struct gcol_data *d) {
    double *offs[7] = { &d->col.h, &d->col.s, &d->col.v, &d->col.r, &d->col.g, &d->col.b, &d->col.alpha };
    int i;
    char text[50];

    gHSV2RGB((struct hslrgb *) &d->col);
    sprintf( text, "%3.0f", *offs[0]);
    GGadgetSetTitle8(GWidgetGetControl(d->gw,cids[0]),text);
    for ( i=1; i<7; ++i ) {
	sprintf( text, "%.2f", *offs[i]);
	GGadgetSetTitle8(GWidgetGetControl(d->gw,cids[i]),text);
    }
}
