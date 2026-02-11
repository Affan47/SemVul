rebuild_rotation_combo (CcDisplayPanel *self)
{
  typedef struct
  {
    GnomeRRRotation	rotation;
    const char *	name;
  } RotationInfo;
  static const RotationInfo rotations[] = {
    { GNOME_RR_ROTATION_0, NC_("display panel, rotation", "Normal") },
    { GNOME_RR_ROTATION_90, NC_("display panel, rotation", "Counterclockwise") },
    { GNOME_RR_ROTATION_270, NC_("display panel, rotation", "Clockwise") },
    { GNOME_RR_ROTATION_180, NC_("display panel, rotation", "180 Degrees") },
  };
  const char *selection;
  GnomeRRRotation current;
  int i;

  clear_combo (self->priv->rotation_combo);

  gtk_widget_set_sensitive (self->priv->rotation_combo,
                            self->priv->current_output && gnome_rr_output_info_is_active (self->priv->current_output));

  if (!self->priv->current_output)
    return;

  current = gnome_rr_output_info_get_rotation (self->priv->current_output);

  selection = NULL;
  for (i = 0; i < G_N_ELEMENTS (rotations); ++i)
    {
      const RotationInfo *info = &(rotations[i]);

      gnome_rr_output_info_set_rotation (self->priv->current_output, info->rotation);


      if (gnome_rr_config_applicable (self->priv->current_configuration, self->priv->screen, NULL))
        {
          add_key (gtk_combo_box_get_model (GTK_COMBO_BOX (self->priv->rotation_combo)), g_dpgettext2 (NULL, "display panel, rotation", info->name), FALSE, 0, 0, 0, info->rotation);

          if (info->rotation == current)
            selection = g_dpgettext2 (NULL, "display panel, rotation", info->name);
        }
    }

  gnome_rr_output_info_set_rotation (self->priv->current_output, current);

  if (!(selection && combo_select (self->priv->rotation_combo, selection)))
    gtk_combo_box_set_active (GTK_COMBO_BOX (self->priv->rotation_combo), 0);
}
