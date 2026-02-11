key_press( GtkTreeView *list, GdkEventKey *event, gpointer user_data )
{
  GtkAdjustment *adjustment = user_data;
  GtkTreePath *path;
  GtkTreeViewColumn *focus_column;
  gdouble base, oldbase, base_limit;
  gdouble page_size, step_increment;
  int cursor_row = 0;
  int num_rows;

  base = oldbase = gtk_adjustment_get_value( adjustment );
  page_size = gtk_adjustment_get_page_size( adjustment );
  step_increment = gtk_adjustment_get_step_increment( adjustment );
  num_rows = ( page_size + 1 ) / step_increment;


  gtk_tree_view_get_cursor( list, &path, &focus_column );
  if( path ) {
    int *indices = gtk_tree_path_get_indices( path );
    if( indices ) cursor_row = indices[0];
    gtk_tree_path_free( path );
  }

  switch( event->keyval )
  {
  case GDK_KEY_Up:
    if( cursor_row == 0 )
      base -= step_increment;
    break;

  case GDK_KEY_Down:
    if( cursor_row == num_rows - 1 )
      base += step_increment;
    break;

  case GDK_KEY_Page_Up:
    base -= gtk_adjustment_get_page_increment( adjustment );
    break;

  case GDK_KEY_Page_Down:
    base += gtk_adjustment_get_page_increment( adjustment );
    break;

  case GDK_KEY_Home:
    cursor_row = 0;
    base = gtk_adjustment_get_lower( adjustment );
    break;

  case GDK_KEY_End:
    cursor_row = num_rows - 1;
    base = gtk_adjustment_get_upper( adjustment ) - page_size;
    break;

  default:
    return FALSE;
  }

  if( base < 0 ) {
    base = 0;
  } else {
    base_limit = gtk_adjustment_get_upper( adjustment ) - page_size;
    if( base > base_limit ) base = base_limit;
  }

  if( base != oldbase ) {
    gtk_adjustment_set_value( adjustment, base );


    path = gtk_tree_path_new_from_indices( cursor_row, -1 );
    gtk_tree_view_set_cursor( list, path, NULL, FALSE );
    gtk_tree_path_free( path );
    return TRUE;
  }

  return FALSE;
}
