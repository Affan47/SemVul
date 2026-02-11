ladish_exit(struct cdbus_method_call * call_ptr)
{
  log_info("Exit command received through D-Bus");

  if (!ladish_command_exit(NULL, ladish_studio_get_cmd_queue()))
  {


    g_quit = true;
  }

  cdbus_method_return_new_void(call_ptr);
}
