elm_notify_timeout_set(Evas_Object *obj,
                       double timeout)
{
   ELM_NOTIFY_CHECK(obj);
   ELM_NOTIFY_DATA_GET(obj, sd);

   sd->timeout = timeout;
   _timer_init(obj, sd);
}
