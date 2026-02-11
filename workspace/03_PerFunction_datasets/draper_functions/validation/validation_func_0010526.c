_gc_shutdown(E_Gadcon_Client *gcc)
{
   Instance *inst;

   if (!(inst = gcc->data)) return;
   instances = eina_list_remove(instances, inst);
   if (inst->poller) ecore_poller_del(inst->poller);
   if (inst->obj) evas_object_del(inst->obj);
   E_FREE(inst);
}
