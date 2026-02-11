get_full_username(char *buf, int buflen,
                                     const struct player *pplayer)
{
  if (!buf || buflen < 1) {
    return;
  }

  if (!pplayer) {
    buf[0] = '\0';
    return;
  }

  if (pplayer->ai_controlled) {

    fc_snprintf(buf, buflen, _("AI %s"), pplayer->name);
  } else {
    fc_strlcpy(buf, pplayer->username, buflen);
  }
}
