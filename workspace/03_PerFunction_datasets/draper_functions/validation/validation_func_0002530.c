gwy_gradient_dump(GwyResource *resource,
                  GString *str)
{
    GwyGradient *gradient;
    GwyGradientPoint *pt;
    gchar buffer[G_ASCII_DTOSTR_BUF_SIZE];
    guint i;

    g_return_if_fail(GWY_IS_GRADIENT(resource));
    gradient = GWY_GRADIENT(resource);
    g_return_if_fail(gradient->points->len > 0);

    for (i = 0; i < gradient->points->len; i++) {
        pt = &g_array_index(gradient->points, GwyGradientPoint, i);

        g_ascii_formatd(buffer, sizeof(buffer), "%.6g", pt->x);
        g_string_append(str, buffer);
        g_string_append_c(str, ' ');
        g_ascii_formatd(buffer, sizeof(buffer), "%.6g", pt->color.r);
        g_string_append(str, buffer);
        g_string_append_c(str, ' ');
        g_ascii_formatd(buffer, sizeof(buffer), "%.6g", pt->color.g);
        g_string_append(str, buffer);
        g_string_append_c(str, ' ');
        g_ascii_formatd(buffer, sizeof(buffer), "%.6g", pt->color.b);
        g_string_append(str, buffer);
        g_string_append_c(str, ' ');
        g_ascii_formatd(buffer, sizeof(buffer), "%g", pt->color.a);
        g_string_append(str, buffer);
        g_string_append_c(str, '\n');
    }
}
