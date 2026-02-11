libgnac_converter_get_property(GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *param)
{
  LibgnacConverter *self = LIBGNAC_CONVERTER(object);

  switch (property_id)
  {
    case PROP_AUDIO_PIPELINE_DESC:
      g_value_set_string(value, self->priv->profile->audio_desc);
    break;

    case PROP_MUXER_PIPELINE_DESC:
      g_value_set_string(value, self->priv->profile->muxer_desc);
    break;

    case PROP_VIDEO_PIPELINE_DESC:
      g_value_set_string(value, self->priv->profile->video_desc);
    break;

    case PROP_STRIP_SPECIAL:
      g_value_set_boolean(value, self->priv->strip_special);
    break;

    case PROP_RENAME_PATTERN:
      g_value_set_string(value, self->priv->rename_pattern);
    break;

    case PROP_FOLDER_HIERARCHY:
      g_value_set_string(value, self->priv->folder_hierarchy);
    break;

    case PROP_FOLDER_TYPE:
      g_value_set_int(value, self->priv->folder_type);
    break;

    case PROP_FOLDER_PATH:
      g_value_set_string(value, self->priv->folder_path);
    break;

    case PROP_EXTENSION:
      g_value_set_string(value, self->priv->extension);
    break;

    case PROP_NB_FILES:
      g_value_set_int(value, g_hash_table_size(self->priv->file_table));
    break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, param);
    break;
  }
}
