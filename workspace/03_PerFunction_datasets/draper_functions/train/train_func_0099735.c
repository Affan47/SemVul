do_focus (CANON_Scanner * s)
{
  SANE_Status status;
  u_char ebuf[74];
  size_t buf_size;

  DBG (3, "do_focus: sending GET FILM STATUS\n");
  memset (ebuf, 0, sizeof (ebuf));
  buf_size = 4;
  status = get_film_status (s->fd, ebuf, &buf_size);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "do_focus: GET FILM STATUS failed\n");
      if (status == SANE_STATUS_UNSUPPORTED)
	return (SANE_STATUS_GOOD);
      else
	{
	  DBG (1, "do_focus: ... for unknown reasons\n");
	  sanei_scsi_close (s->fd);
	  s->fd = -1;
	  return (SANE_STATUS_INVAL);
	}
    }
  DBG (3, "focus point before autofocus : %d\n", ebuf[3]);

  status = execute_auto_focus (s->fd, s->val[OPT_AF].w,
    (s->scanning_speed == 0 && !s->RIF && s->hw->info.model == CS2700),
    (int) s->AE, s->val[OPT_FOCUS].w);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (7, "execute_auto_focus failed\n");
      if (status == SANE_STATUS_UNSUPPORTED)
	  return (SANE_STATUS_GOOD);
      else
	{
	  DBG (1, "do_focus: ... for unknown reasons\n");
	  sanei_scsi_close (s->fd);
	  s->fd = -1;
	  return (SANE_STATUS_INVAL);
	}
    }

  DBG (3, "do_focus: sending GET FILM STATUS\n");
  memset (ebuf, 0, sizeof (ebuf));
  buf_size = 4;
  status = get_film_status (s->fd, ebuf, &buf_size);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "do_focus: GET FILM STATUS failed\n");
      if (status == SANE_STATUS_UNSUPPORTED)
	  return (SANE_STATUS_GOOD);
      else
	{
	  DBG (1, "do_focus: ... for unknown reasons\n");
	  sanei_scsi_close (s->fd);
	  s->fd = -1;
	  return (SANE_STATUS_INVAL);
	}
    }
  else
      DBG (3, "focus point after autofocus : %d\n", ebuf[3]);

  return (SANE_STATUS_GOOD);
}
