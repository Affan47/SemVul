msg_unmarshal(struct msg *tmp,  struct evbuffer *evbuf)
{
  ev_uint32_t tag;
  while (EVBUFFER_LENGTH(evbuf) > 0) {
    if (evtag_peek(evbuf, &tag) == -1)
      return (-1);
    switch (tag) {

      case MSG_FROM_NAME:

        if (tmp->from_name_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, MSG_FROM_NAME, &tmp->from_name_data) == -1) {
          event_warnx("%s: failed to unmarshal from_name", __func__);
          return (-1);
        }
        tmp->from_name_set = 1;
        break;

      case MSG_TO_NAME:

        if (tmp->to_name_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, MSG_TO_NAME, &tmp->to_name_data) == -1) {
          event_warnx("%s: failed to unmarshal to_name", __func__);
          return (-1);
        }
        tmp->to_name_set = 1;
        break;

      case MSG_ATTACK:

        if (tmp->attack_set)
          return (-1);
        tmp->attack_data = kill_new();
        if (tmp->attack_data == NULL)
          return (-1);
        if (evtag_unmarshal_kill(evbuf, MSG_ATTACK, tmp->attack_data) == -1) {
          event_warnx("%s: failed to unmarshal attack", __func__);
          return (-1);
        }
        tmp->attack_set = 1;
        break;

      case MSG_RUN:

        if (msg_run_add(tmp) == NULL)
          return (-1);
        if (evtag_unmarshal_run(evbuf, MSG_RUN,
          tmp->run_data[tmp->run_length - 1]) == -1) {
          --tmp->run_length;
          event_warnx("%s: failed to unmarshal run", __func__);
          return (-1);
        }
        tmp->run_set = 1;
        break;

      default:
        return -1;
    }
  }

  if (msg_complete(tmp) == -1)
    return (-1);
  return (0);
}
