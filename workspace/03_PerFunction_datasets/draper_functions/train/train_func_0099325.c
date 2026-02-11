mark_row( GtkTreeModel *model, int row )
{
  GtkTreeIter iter;
  GtkTreePath *path;

  path = gtk_tree_path_new_from_indices( row, -1 );

  if( !gtk_tree_model_get_iter( model, &iter, path ) ) {
    gtk_tree_path_free( path );
    return;
  }

  gtk_tree_path_free( path );

  gtk_list_store_set( GTK_LIST_STORE( model ), &iter,
                      COL_PIX, tape_marker_pixbuf,
                      -1 );
}
