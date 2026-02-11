clutter_text_real_line_end (ClutterText         *self,
                            const gchar         *action,
                            guint                keyval,
                            ClutterModifierType  modifiers)
{
  ClutterTextPrivate *priv = self->priv;
  gint position;

  g_object_freeze_notify (G_OBJECT (self));

  position = clutter_text_move_line_end (self, priv->position);
  clutter_text_set_cursor_position (self, position);

  if (!(priv->selectable && (modifiers & CLUTTER_SHIFT_MASK)))
    clutter_text_clear_selection (self);

  g_object_thaw_notify (G_OBJECT (self));

  return TRUE;
}
