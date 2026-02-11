gwy_data_field_get_linear_area_size(gint width, gint height)
{
    return MAX(width, ABS(height));
}
