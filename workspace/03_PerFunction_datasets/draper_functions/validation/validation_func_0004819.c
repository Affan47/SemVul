my_progressbar_test_start(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   elm_progressbar_pulse(_test_progressbar.pb2, EINA_TRUE);
   elm_progressbar_pulse(_test_progressbar.pb5, EINA_TRUE);
   elm_progressbar_pulse(_test_progressbar.pb7, EINA_TRUE);
   if (!_test_progressbar.run)
     {
        _test_progressbar.timer = ecore_timer_add(0.1, _my_progressbar_value_set, NULL);
        _test_progressbar.run = EINA_TRUE;
     }
}
