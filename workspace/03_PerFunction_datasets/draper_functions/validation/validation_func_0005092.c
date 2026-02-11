static_ok_local (gamgi_window *window_dialog)
{
gamgi_window *window_mouse;
gamgi_layer *layer;
gamgi_light *light;
GtkWidget *dialog = window_dialog->dialog0;

cache.local = TRUE;


light = GAMGI_CAST_LIGHT gamgi_gtk_object_name_number (dialog,
"entry_light", GAMGI_ENGINE_LIGHT, window_dialog);
if (light == NULL)
  {
  gamgi_gtk_dialog_message_create ("Error",
  "Invalid light object", window_dialog);
  return;
  }

if (static_grab (window_dialog) == FALSE) return;


if (static_apply (light, window_dialog) == FALSE) return;


if (cache.layer == NULL)
  layer = gamgi_engine_find_layer (GAMGI_CAST_OBJECT light);
else
  layer = cache.layer;


gamgi_gtk_object_copy (GAMGI_CAST_OBJECT light,
GAMGI_CAST_OBJECT layer, window_dialog);


window_mouse =  GAMGI_CAST_WINDOW layer->object.object;
gtk_widget_queue_draw (window_mouse->area);

static_reset (window_dialog);
}
