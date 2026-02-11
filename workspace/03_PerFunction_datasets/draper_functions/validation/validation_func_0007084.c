_elm_scroll_freeze_set(Evas_Object *obj,
                       Eina_Bool freeze)
{
   ELM_SCROLL_IFACE_DATA_GET_OR_RETURN(obj, sid);

   sid->freeze = freeze;
   if (sid->freeze)
     {
        if (sid->down.onhold_animator)
          {
             ecore_animator_del(sid->down.onhold_animator);
             sid->down.onhold_animator = NULL;
             if (sid->content_info.resized)
               _elm_scroll_wanted_region_set(sid->obj);
          }
     }
   else
     _elm_scroll_bounce_eval(sid);
}
