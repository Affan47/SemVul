plot_pixel_safe(GwyDataField *dfield, gint idx, gdouble value)
{
    if (idx > 0 && idx < dfield->xres*dfield->yres)
        dfield->data[idx] += value;
}
