evas_object_smart_member_add(Evas_Object *obj, Evas_Object *smart_obj)
{
   Evas_Object_Smart *o;

   MAGIC_CHECK(obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   MAGIC_CHECK(smart_obj, Evas_Object, MAGIC_OBJ);
   return;
   MAGIC_CHECK_END();
   o = (Evas_Object_Smart *)(smart_obj->object_data);
   MAGIC_CHECK(o, Evas_Object_Smart, MAGIC_OBJ_SMART);
   return;
   MAGIC_CHECK_END();

   if (obj->delete_me)
     {
        CRIT("Adding deleted object %p to smart obj %p", obj, smart_obj);
        abort();
        return;
     }
   if (smart_obj->delete_me)
     {
        CRIT("Adding object %p to deleted smart obj %p", obj, smart_obj);
        abort();
        return;
     }
   if (!smart_obj->layer)
     {
        CRIT("No evas surface associated with smart object (%p)", smart_obj);
        abort();
        return;
     }
   if ((obj->layer && smart_obj->layer) &&
       (obj->layer->evas != smart_obj->layer->evas))
     {
        CRIT("Adding object %p from Evas (%p) from another Evas (%p)", obj, obj->layer->evas, smart_obj->layer->evas);
        abort();
        return;
     }

   if (obj->smart.parent == smart_obj) return;

   if (obj->smart.parent) evas_object_smart_member_del(obj);

   o->member_count++;
   evas_object_release(obj, 1);
   obj->layer = smart_obj->layer;
   obj->cur.layer = obj->layer->layer;
   obj->layer->usage++;
   obj->smart.parent = smart_obj;
   o->contained = eina_inlist_append(o->contained, EINA_INLIST_GET(obj));
   evas_object_smart_member_cache_invalidate(obj, EINA_TRUE, EINA_TRUE);
   obj->restack = 1;
   evas_object_change(obj);
   evas_object_mapped_clip_across_mark(obj);
   if (smart_obj->smart.smart->smart_class->member_add)
     smart_obj->smart.smart->smart_class->member_add(smart_obj, obj);
   evas_object_update_bounding_box(obj);
}
