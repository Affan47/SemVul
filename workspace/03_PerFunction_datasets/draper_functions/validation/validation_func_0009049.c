p_font_callback   (gchar    *name
                  ,gboolean  dialog_closing
                  ,gpointer  user_data)
{
  GapArrArg *arr_ptr;

  if(gap_debug) printf("p_font_callback: %s  closing:%d\n", name, (int)dialog_closing);

  arr_ptr = (GapArrArg *)user_data;
  if(arr_ptr)
  {
    g_snprintf(arr_ptr->text_buf_ret, arr_ptr->text_buf_len, "%s", name);
    gtk_entry_set_text(GTK_ENTRY(arr_ptr->text_entry), arr_ptr->text_buf_ret);
  }

  if(dialog_closing)
  {
    arr_ptr->text_fontsel = NULL;
  }
}
