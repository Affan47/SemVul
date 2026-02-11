possible_click( GtkTreeView *treeview GCC_UNUSED, GtkTreePath *path,
                GtkTreeViewColumn *col GCC_UNUSED,
                gpointer user_data GCC_UNUSED )
{
  int error, *indices, row;


  indices = gtk_tree_path_get_indices( path );
  if( !indices ) return;
  row = indices[0];

  error = debugger_breakpoint_add_address(
    DEBUGGER_BREAKPOINT_TYPE_WRITE, memory_source_ram, possible_page[ row ],
    possible_offset[ row ], 0, DEBUGGER_BREAKPOINT_LIFE_PERMANENT, NULL
  );
  if( error ) return;

  ui_debugger_update();
}
