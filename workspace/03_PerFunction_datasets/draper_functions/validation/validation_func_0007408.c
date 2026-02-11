gl124_update_hardware_sensors (Genesys_Scanner * s)
{


  SANE_Status status = SANE_STATUS_GOOD;
  uint8_t val=0;

  RIE (sanei_genesys_read_register (s->dev, REG31, &val));


  if(s->dev->model->gpo_type == GPO_CANONLIDE110)
    {
      if (s->val[OPT_SCAN_SW].b == s->last_val[OPT_SCAN_SW].b)
        s->val[OPT_SCAN_SW].b = (val & 0x01) == 0;
      if (s->val[OPT_FILE_SW].b == s->last_val[OPT_FILE_SW].b)
        s->val[OPT_FILE_SW].b = (val & 0x08) == 0;
      if (s->val[OPT_EMAIL_SW].b == s->last_val[OPT_EMAIL_SW].b)
        s->val[OPT_EMAIL_SW].b = (val & 0x04) == 0;
      if (s->val[OPT_COPY_SW].b == s->last_val[OPT_COPY_SW].b)
        s->val[OPT_COPY_SW].b = (val & 0x02) == 0;
    }
  else
    {
      if (s->val[OPT_EXTRA_SW].b == s->last_val[OPT_EXTRA_SW].b)
        s->val[OPT_EXTRA_SW].b = (val & 0x01) == 0;
      if (s->val[OPT_SCAN_SW].b == s->last_val[OPT_SCAN_SW].b)
        s->val[OPT_SCAN_SW].b = (val & 0x02) == 0;
      if (s->val[OPT_COPY_SW].b == s->last_val[OPT_COPY_SW].b)
        s->val[OPT_COPY_SW].b = (val & 0x04) == 0;
      if (s->val[OPT_EMAIL_SW].b == s->last_val[OPT_EMAIL_SW].b)
        s->val[OPT_EMAIL_SW].b = (val & 0x08) == 0;
      if (s->val[OPT_FILE_SW].b == s->last_val[OPT_FILE_SW].b)
        s->val[OPT_FILE_SW].b = (val & 0x10) == 0;
    }
  return status;
}
