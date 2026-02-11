kill_marshal(struct evbuffer *evbuf, const struct kill *tmp){
  evtag_marshal_string(evbuf, KILL_WEAPON, tmp->weapon_data);
  evtag_marshal_string(evbuf, KILL_ACTION, tmp->action_data);
  if (tmp->how_often_set) {
    {
      int i;
      for (i = 0; i < tmp->how_often_length; ++i) {
    evtag_marshal_int(evbuf, KILL_HOW_OFTEN, tmp->how_often_data[i]);
      }
    }
  }
}
