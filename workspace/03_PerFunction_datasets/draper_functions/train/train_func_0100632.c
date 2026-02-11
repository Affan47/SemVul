pattern_toggled (GtkWidget * widget, GladeLabelEditor * label_editor)
{
  GladeLabelEditorPrivate *priv = label_editor->priv;
  GladeProperty *property;
  GladeWidget   *gwidget = glade_editable_loaded_widget (GLADE_EDITABLE (label_editor));

  if (glade_editable_loading (GLADE_EDITABLE (label_editor)) || !gwidget)
    return;

  if (!gtk_toggle_button_get_active
      (GTK_TOGGLE_BUTTON (priv->pattern_radio)))
    return;

  glade_editable_block (GLADE_EDITABLE (label_editor));

  glade_command_push_group (_("Setting %s to use a pattern string"),
                            glade_widget_get_name (gwidget));

  property = glade_widget_get_property (gwidget, "glade-attributes");
  glade_command_set_property (property, NULL);
  property = glade_widget_get_property (gwidget, "use-markup");
  glade_command_set_property (property, FALSE);
  property = glade_widget_get_property (gwidget, "label-content-mode");
  glade_command_set_property (property, GLADE_LABEL_MODE_PATTERN);

  glade_command_pop_group ();

  glade_editable_unblock (GLADE_EDITABLE (label_editor));


  glade_editable_load (GLADE_EDITABLE (label_editor), gwidget);
}
