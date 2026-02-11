evas_common_font_instance_descent_get(RGBA_Font_Int *fi)
{
   int val;
   evas_common_font_int_reload(fi);
   if (fi->src->current_size != fi->size)
     {
        FTLOCK();
        FT_Activate_Size(fi->ft.size);
        FTUNLOCK();
        fi->src->current_size = fi->size;
     }
   val = -(int)fi->src->ft.face->size->metrics.descender;
   return FONT_METRIC_ROUNDUP(val);


}
