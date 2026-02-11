_pan_max_get(Evas_Object *obj, Evas_Coord *x, Evas_Coord *y)
{
   Smart_Data *sd = evas_object_smart_data_get(obj);
   if (x)
     {
        if (sd->w < sd->cw) *x = sd->cw - sd->w;
        else *x = 0;
     }
   if (y)
     {
        if (sd->h < sd->ch) *y = sd->ch - sd->h;
        else *y = 0;
     }
}
