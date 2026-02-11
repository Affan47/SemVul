sge_event_master_wait_next(void)
{

   DENTER(TOP_LAYER, "sge_event_master_wait_next");

   sge_mutex_lock("event_master_cond_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.cond_mutex);

   if (!Event_Master_Control.delivery_signaled) {
      u_long32 current_time = sge_get_gmt();
      struct timespec ts;
      ts.tv_sec = (time_t)(current_time + EVENT_DELIVERY_INTERVAL_S);
      ts.tv_nsec = EVENT_DELIVERY_INTERVAL_N;
      pthread_cond_timedwait(&Event_Master_Control.cond_var, &Event_Master_Control.cond_mutex, &ts);
   }

   Event_Master_Control.delivery_signaled = false;

   sge_mutex_unlock("event_master_cond_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.cond_mutex);


   DRETURN_VOID;
}
