elm_layout_box_remove(Evas_Object *obj,
                      const char *part,
                      Evas_Object *child)
{
   ELM_LAYOUT_CHECK(obj) NULL;
   ELM_LAYOUT_DATA_GET_OR_RETURN_VAL(obj, sd, NULL);

   return ELM_LAYOUT_CLASS(ELM_WIDGET_DATA(sd)->api)->box_remove
            (obj, part, child);
}
