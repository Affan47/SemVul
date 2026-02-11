p_attw_gdouble_adjustment_callback(GtkObject *obj, gdouble *val)
{
  GapStbAttrWidget *attw;
  gdouble l_val;


  attw = g_object_get_data( G_OBJECT(obj), OBJ_DATA_KEY_ATTW );
  if(attw)
  {
    if(attw->stb_elem_refptr)
    {
      l_val = (GTK_ADJUSTMENT(obj)->value) / CONVERT_TO_100PERCENT;
      if(gap_debug)
      {
        printf("gdouble_adjustment_callback: old_val:%f val:%f\n"
          , (float)*val
          , (float)l_val
          );
      }
      if(l_val != *val)
      {
        p_attw_push_undo_and_set_unsaved_changes(attw);
        *val = l_val;
        p_attw_update_properties(attw);
      }
    }
  }

}
