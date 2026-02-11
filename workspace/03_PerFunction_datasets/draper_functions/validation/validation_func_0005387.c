ec2_evco_triggered(sge_evc_class_t *thiz) {
   bool ret = false;
   ec_control_t *evco = NULL;

   DENTER(EVC_LAYER, "ec2_evco_triggered");
   if (thiz == NULL) {
      DRETURN(false);
   }
   evco = ec2_get_event_control(thiz);
   if (evco == NULL) {
      DRETURN(false);
   }
   sge_mutex_lock("event_control_mutex", SGE_FUNC, __LINE__, &(evco->mutex));
   ret = evco->triggered;
   sge_mutex_unlock("event_control_mutex", SGE_FUNC, __LINE__, &(evco->mutex));

   DRETURN(ret);
}
