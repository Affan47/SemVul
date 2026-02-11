loc_tree_float_cell_data_function (GtkTreeViewColumn *col,
                                           GtkCellRenderer   *renderer,
                                           GtkTreeModel      *model,
                                           GtkTreeIter       *iter,
                                           gpointer           column)
{
     gfloat   number;
     gchar   *buff;
     guint    coli = GPOINTER_TO_UINT (column);
     gchar    hmf = ' ';

     gtk_tree_model_get (model, iter, coli, &number, -1);


     if (sat_cfg_get_bool (SAT_CFG_BOOL_USE_NSEW)) {

          if (coli == TREE_COL_LAT) {
               if (number < 0.0) {
                    number *= -1.0;
                    hmf = 'S';
               }
               else {
                    hmf = 'N';
               }
          }
          else if (coli == TREE_COL_LON) {
               if (number < 0.0) {
                    number *= -1.0;
                    hmf = 'W';
               }
               else {
                    hmf = 'E';
               }
          }
          else {
               sat_log_log (SAT_LOG_LEVEL_BUG,
                               _("%s: Invalid column: %d"),
                               __FUNCTION__, coli);
               hmf = '?';
          }
     }

     if (fabs (LTMN-number) > LTEPS) {
          buff = g_strdup_printf ("%.4f\302\260%c", number, hmf);
     }
     else {
          buff = g_strdup ("");
     }

     g_object_set (renderer, "text", buff, NULL);
     g_free (buff);
}
