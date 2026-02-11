rating_changed ( GtkRange *range,
                             gpointer user_data ) {
    GList * llist;
    song * s;
    gboolean had_color_rating;
    gdouble val;

    val = gtk_range_get_value(range);

    for (llist = g_list_first(gjay->selected_songs); llist;
         llist = g_list_next(llist)) {
        s = (song *) llist->data;

        if (s->no_color | s->no_rating) {
            had_color_rating = FALSE;
        } else {
            had_color_rating = TRUE;
        }

        s->no_rating = FALSE;
        s->rating = val;

        song_set_repeat_attrs(s);


        if (!had_color_rating) {
            update_song_has_rating_color(s);
        }
    }
    gtk_label_set_text (GTK_LABEL(label_rating), "Rating");

    gjay->songs_dirty = TRUE;
}
