fx_bus(GstBus* bus, GstMessage* msg, gpointer data)
{
  switch( GST_MESSAGE_TYPE( msg ) )
    {
    case GST_MESSAGE_EOS:
      g_debug("fx_bus: EOS START");
      gc_sound_fx_close();

      g_idle_add(run_sound_callback, data);
      fx_play();
      g_debug("fx_bus: EOS END");
      break;
    default:
      return TRUE;
    }

  return FALSE;
}
