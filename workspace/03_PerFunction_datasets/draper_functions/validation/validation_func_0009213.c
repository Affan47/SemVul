gene_orb_num(GtkWidget *b,gpointer data)
{
  GtkWidget **entryall;
  GtkWidget *entry;
  G_CONST_RETURN gchar *entrytext;
  guint i;
  entryall=(GtkWidget **)data;
  for (i=0;i<8;i++)
  {
  entry=entryall[i];
  entrytext = gtk_entry_get_text(GTK_ENTRY(entry));
  gabedit_text_insert (GABEDIT_TEXT(text2), NULL, NULL, NULL, ",",-1);
  gabedit_text_insert (GABEDIT_TEXT(text2), NULL, NULL, NULL, entrytext,-1);
  }
  gabedit_text_insert (GABEDIT_TEXT(text2), NULL, NULL, NULL, "; ",-1);
}
