gui_editor_toggle_mark_at_line (GUIEditor * self, gint line_no)
{
  g_assert (self);

  GtkTextIter line_start, line_end;
  GSList *marker_list;
  GtkSourceMark *marker;


  gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (self->buffer), &line_start, line_no);
  line_end = line_start;
  gtk_text_iter_forward_to_line_end (&line_end);


  marker_list = gtk_source_buffer_get_source_marks_at_line (self->buffer, line_no, MARKER_BREAKPOINT);

  if (marker_list != NULL && g_slist_length(marker_list)!=0)
	{

	  gtk_source_buffer_remove_source_marks (self->buffer,  &line_start, &line_end, MARKER_BREAKPOINT);
	}
  else
	{

	  marker = gtk_source_buffer_create_source_mark (self->buffer, NULL, MARKER_BREAKPOINT, &(line_start));
	}
  g_slist_free (marker_list);

}
