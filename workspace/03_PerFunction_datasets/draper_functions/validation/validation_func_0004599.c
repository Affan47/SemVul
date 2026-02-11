cmor_set_variable_attribute(int id, char *attribute_name, char type, void *value)
{
  char msg[CMOR_MAX_STRING];
  cmor_add_traceback("cmor_set_variable_attribute");


  if (
      (strcmp(attribute_name,"units")==0) ||
      (strcmp(attribute_name,"missing_values")==0) ||
      (strcmp(attribute_name,"_FillValue")==0) ||
      (strcmp(attribute_name,"standard_name")==0) ||
      (strcmp(attribute_name,"long_name")==0) ||
      (strcmp(attribute_name,"flag_values")==0) ||
      (strcmp(attribute_name,"flag_meaning")==0) ||
      (strcmp(attribute_name,"comment")==0) ||
      (strcmp(attribute_name,"history")==0) ||
      (strcmp(attribute_name,"original_name")==0) ||
      (strcmp(attribute_name,"original_units")==0) ||
      (strcmp(attribute_name,"positive")==0) ||
      (strcmp(attribute_name,"cell_methods")==0)
      )
    {
      snprintf(msg,CMOR_MAX_STRING,"variable attribute %s (vor variable %s, table %s) must be set via a call to cmor_variable or it is automaticaly set via the tables",attribute_name,cmor_vars[id].id,cmor_tables[cmor_vars[id].ref_table_id].table_id);
      cmor_handle_error(msg,CMOR_NORMAL);
      cmor_pop_traceback();
      return 1;
    }

  if (cmor_vars[id].initialized!=-1) {
    snprintf(msg,CMOR_MAX_STRING,"attribute %s on variable %s (table %s) will probably not be set as the variable has already been created into the output NetCDF file, please place this call BEFORE any cal to cmor_write",attribute_name,cmor_vars[id].id,cmor_tables[cmor_vars[id].ref_table_id].table_id);
    cmor_handle_error(msg,CMOR_NORMAL);
    cmor_pop_traceback();
    return 1;
  }
  cmor_pop_traceback();
  return cmor_set_variable_attribute_internal(id,attribute_name,type,value);
}
