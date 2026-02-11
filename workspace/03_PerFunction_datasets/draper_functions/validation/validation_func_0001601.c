te_add_event(te_event_t anEvent)
{
   time_t when = 0;
   lListElem *le;

   DENTER(EVENT_LAYER, "te_add_event");

   SGE_ASSERT((anEvent != NULL));

   when = (ONE_TIME_EVENT == anEvent->mode) ? anEvent->when : (time(NULL) + anEvent->interval);

   le = lCreateElem(TE_Type);
   lSetUlong(le,  TE_when,     when);
   lSetUlong(le,  TE_type,     anEvent->type);
   lSetUlong(le,  TE_mode,     anEvent->mode);
   lSetUlong(le,  TE_interval, anEvent->interval);
   lSetUlong(le,  TE_uval0,    anEvent->ulong_key_1);
   lSetUlong(le,  TE_uval1,    anEvent->ulong_key_2);
   lSetString(le, TE_sval,     anEvent->str_key);

   DPRINTF(("%s: (t:"sge_u32" w:"sge_u32" m:"sge_u32" s:%s)\n", SGE_FUNC, anEvent->type,
      when, anEvent->mode, anEvent->str_key?anEvent->str_key:MSG_SMALLNULL));

   sge_mutex_lock("event_control_mutex", SGE_FUNC, __LINE__, &Event_Control.mutex);

   lSetUlong(le, TE_seqno, Event_Control.seq_no++);

   if (lInsertSorted(Event_Control.sort_order, le, Event_Control.list) != 0) {
      lFreeElem(&le);
   }

   if ((Event_Control.next == 0) || (when < Event_Control.next)) {
      Event_Control.next = when;

      pthread_cond_signal(&Event_Control.cond_var);

      DPRINTF(("%s: did signal delivery thread!\n", SGE_FUNC));
   }

   sge_mutex_unlock("event_control_mutex", SGE_FUNC, __LINE__, &Event_Control.mutex);

   DRETURN_VOID;
}
