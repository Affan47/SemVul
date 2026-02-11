remove_capslock_feedback (StEntry *entry)
{
  if (entry->priv->capslock_warning_shown)
    {
      st_entry_set_secondary_icon (entry, NULL);
      entry->priv->capslock_warning_shown = FALSE;
    }
}
