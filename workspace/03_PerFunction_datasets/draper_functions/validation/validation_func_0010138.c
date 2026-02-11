external_photocam_param_get(void *data __UNUSED__, const Evas_Object *obj, Edje_External_Param *param)
{
   if (!strcmp(param->name, "file"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
	  {
	     param->s = elm_photocam_file_get(obj);
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "zoom"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_DOUBLE)
	  {
	     param->d = elm_photocam_zoom_get(obj);
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "zoom mode"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_STRING)
	  {
	     Elm_Photocam_Zoom_Mode zoom_mode_set = elm_photocam_zoom_mode_get(obj);

	     if (zoom_mode_set == ELM_PHOTOCAM_ZOOM_MODE_LAST)
	       return EINA_FALSE;

	     param->s = choices[zoom_mode_set];
	     return EINA_TRUE;
	  }
     }
   else if (!strcmp(param->name, "paused"))
     {
	if (param->type == EDJE_EXTERNAL_PARAM_TYPE_BOOL)
	  {
	     param->i = elm_photocam_paused_get(obj);
	     return EINA_TRUE;
	  }
     }

   ERR("unknown parameter '%s' of type '%s'",
       param->name, edje_external_param_type_str(param->type));

   return EINA_FALSE;
}
