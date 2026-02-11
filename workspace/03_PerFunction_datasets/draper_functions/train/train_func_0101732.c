Java_com_sun_grid_jgdi_jni_EventClientImpl_fillEvents(JNIEnv *env, jobject evcobj, jint evc_index, jobject eventList)
{
   lList *elist = NULL;
   lList *alp = NULL;
   lListElem *ev = NULL;
   sge_evc_elem_t *elem = NULL;
   jgdi_result_t ret = JGDI_SUCCESS;
   jobject logger = NULL;
   rmon_ctx_t rmon_ctx;

   DENTER(JGDI_LAYER, "Java_com_sun_grid_jgdi_jni_EventClientImpl_fillEvents");

   jgdi_init_rmon_ctx(env, JGDI_EVENT_LOGGER, &rmon_ctx);
   rmon_set_thread_ctx(&rmon_ctx);

   logger = jgdi_get_logger(env, JGDI_EVENT_LOGGER);
   if (jgdi_is_loggable(env, logger, FINER)) {
      jgdi_log(env, logger, FINER, "before ec_get");
   }
   ret = waitEVC("Java_com_sun_grid_jgdi_jni_EventClientImpl_fillEvents wait", evc_index, &elist, &alp);
   if (ret != JGDI_SUCCESS) {
      throw_error_from_answer_list(env, ret, alp);
      goto error;
   }
   if (jgdi_is_loggable(env, logger, FINER)) {
      jgdi_log(env, logger, FINER, "after ec_get");
   }

   for_each(ev, elist) {

      if (jgdi_is_loggable(env, logger, FINER)) {
         jgdi_log(env, logger, FINER, "before process_event");
      }

      ret = process_event(env, eventList, ev, &alp);

      if (jgdi_is_loggable(env, logger, FINER)) {
         jgdi_log(env, logger, FINER, "after process_event");
      }

      if (ret != JGDI_SUCCESS) {

         if (jgdi_is_loggable(env, logger, WARNING)) {

            dstring ds = DSTRING_INIT;

            answer_list_to_dstring(alp, &ds);
            lFreeList(&alp);
            jgdi_log(env, logger, WARNING, sge_dstring_get_string(&ds));
            sge_dstring_free(&ds);
         }
      }
   }
   lFreeList(&elist);

   if (jgdi_is_loggable(env, logger, FINER)) {
      jgdi_log(env, logger, FINER, "before ec_wait");
   }

   if ((ret = lockEVC("Java_com_sun_grid_jgdi_jni_EventClientImpl_fillEvents 2", evc_index, &elem, &alp)) == JGDI_SUCCESS) {
      if (elem->state == RUNNING) {
         elem->sge_evc->ec_wait(elem->sge_evc);
      }
      unlockEVC("Java_com_sun_grid_jgdi_jni_EventClientImpl_fillEvents 2", evc_index);
   } else {
      throw_error_from_answer_list(env, ret, alp);
      goto error;
   }
   if (jgdi_is_loggable(env, logger, FINER)) {
      jgdi_log(env, logger, FINER, "after ec_wait");
   }


   {
      jint size = 0;
      if ((ret = List_size(env, eventList, &size, &alp)) != JGDI_SUCCESS) {
         throw_error_from_answer_list(env, JGDI_ILLEGAL_STATE, alp);
      }
      DPRINTF(("Received %d events\n", size));
   }

error:

   lFreeList(&alp);
   rmon_set_thread_ctx(NULL);
   jgdi_destroy_rmon_ctx(&rmon_ctx);

   DRETURN_VOID;
}
