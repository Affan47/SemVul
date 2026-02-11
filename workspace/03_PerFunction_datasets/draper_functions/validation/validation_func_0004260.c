_evas_object_layer_set_child(Evas_Object *obj, Evas_Object *par, short l)
{
   if (obj->delete_me) return;
   if (obj->cur.layer == l) return;
   evas_object_release(obj, 1);
   obj->cur.layer = l;
   obj->layer = par->layer;
   obj->layer->usage++;
   if (obj->smart.smart)
     {
        Eina_Inlist *contained;
        Evas_Object *member;

        contained = (Eina_Inlist *)evas_object_smart_members_get_direct(obj);
        EINA_INLIST_FOREACH(contained, member)
          {
             _evas_object_layer_set_child(member, obj, l);
          }
     }
}
