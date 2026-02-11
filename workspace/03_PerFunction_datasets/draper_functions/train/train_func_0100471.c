_ecore_timer_del(Ecore_Timer *timer)
{
   if (timer->frozen && !timer->references)
     {
        void *data = timer->data;

        suspended = (Ecore_Timer *)eina_inlist_remove(EINA_INLIST_GET(suspended), EINA_INLIST_GET(timer));

        if (timer->delete_me)
          timers_delete_me--;

        ecore_timer_mp_free(timer);
        return data;
     }

   EINA_SAFETY_ON_TRUE_RETURN_VAL(timer->delete_me, NULL);
   timer->delete_me = 1;
   timers_delete_me++;
   return timer->data;
}
