e_widget_check_checked_get(Evas_Object *check)
{
   E_Widget_Data *wd;
   int ret;

   wd = e_widget_data_get(check);
   if (wd->valptr)
     ret = *(wd->valptr);
   else
     ret = -1;

   return ret;
}
