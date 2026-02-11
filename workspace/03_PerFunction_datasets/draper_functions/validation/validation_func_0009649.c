gm_audio_setting_mask_is_empty (const GMAudioSettingMask *mask)
{
  const unsigned int *p = (const unsigned int *) mask;
  const unsigned int *end = p + (sizeof (GMAudioSettingMask) /
                                 sizeof (unsigned int));

  while (p < end)
  {
    if (*p != 0)
      return FALSE;
    ++p;
  }

  return TRUE;
}
