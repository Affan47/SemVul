prepare_and_exec_update (sqlite3 *db,
			 const gchar *source_id,
			 const gchar *media_id,
			 GList *col_names,
			 GList *keys,
			 GrlMedia *media)
{
  gchar *sql;
  gint r;
  GList *iter_names;
  GString *sql_buf;
  gchar *sql_set;

  GRL_DEBUG ("prepare_and_exec_update");


  sql_buf = g_string_new ("type_id=?");
  iter_names = col_names;
  while (iter_names) {
    gchar *col_name = (gchar *) iter_names->data;
    if (col_name) {
      g_string_append_printf (sql_buf, " , %s=?", col_name);
    }
    iter_names = g_list_next (iter_names);
  }
  sql_set = g_string_free (sql_buf, FALSE);


  sql = g_strdup_printf (GRL_SQL_UPDATE_METADATA, sql_set);
  r = bind_and_exec (db, sql, source_id, media_id, col_names, keys, media);
  g_free (sql);
  g_free (sql_set);

  return r;
}
