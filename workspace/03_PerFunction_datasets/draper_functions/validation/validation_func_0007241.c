_e_init_cb_signal_done_ok(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const char *emission __UNUSED__, const char *source __UNUSED__)
{
   e_init_hide();
   if (_e_init_timeout_timer)
     {
        ecore_timer_del(_e_init_timeout_timer);
        _e_init_timeout_timer = NULL;
     }
   ecore_main_loop_quit();
}
