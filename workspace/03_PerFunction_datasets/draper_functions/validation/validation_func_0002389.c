lgl_template_frame_get_origins (const lglTemplateFrame *frame)
{
        gint               i_label, n_labels, ix, iy;
        lglTemplateOrigin *origins;
        GList             *p;
        lglTemplateLayout *layout;

        g_return_val_if_fail (frame, NULL);

        n_labels = lgl_template_frame_get_n_labels (frame);
        origins = g_new0 (lglTemplateOrigin, n_labels);

        i_label = 0;
        for ( p=frame->all.layouts; p != NULL; p=p->next )
        {
                layout = (lglTemplateLayout *)p->data;

                for (iy = 0; iy < layout->ny; iy++)
                {
                        for (ix = 0; ix < layout->nx; ix++, i_label++)
                        {
                                origins[i_label].x = ix*layout->dx + layout->x0;
                                origins[i_label].y = iy*layout->dy + layout->y0;
                        }
                }
        }

        g_qsort_with_data (origins, n_labels, sizeof(lglTemplateOrigin),
                           compare_origins, NULL);

        return origins;
}
