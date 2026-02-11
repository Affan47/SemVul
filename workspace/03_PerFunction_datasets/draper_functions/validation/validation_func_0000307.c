xsh_table_edge_prepare(const char* name)
{
  cpl_table* tab=NULL;
  int nrow=0;

  check(tab=cpl_table_load(name,2,0));

  nrow=cpl_table_get_nrow(tab);

  cpl_table_new_column(tab,"OBJ_LOW_X",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_CEN_X",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_UPP_X",CPL_TYPE_DOUBLE);

  cpl_table_fill_column_window(tab,"OBJ_LOW_X",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_CEN_X",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_UPP_X",0,nrow,-1);

  cpl_table_new_column(tab,"OBJ_LOW_S",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_LOW_W",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_CEN_S",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_CEN_W",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_UPP_S",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"OBJ_UPP_W",CPL_TYPE_DOUBLE);

  cpl_table_fill_column_window(tab,"OBJ_LOW_S",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_LOW_W",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_CEN_S",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_CEN_W",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_UPP_S",0,nrow,-1);
  cpl_table_fill_column_window(tab,"OBJ_UPP_W",0,nrow,-1);

 cleanup:
  return tab;

}
