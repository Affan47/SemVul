detach_conf(struct Client *client_p, ConfType type)
{
  dlink_node *ptr, *next_ptr;
  struct ConfItem *conf;
  struct ClassItem *aclass;
  struct AccessItem *aconf;
  struct ConfItem *aclass_conf;
  struct MatchItem *match_item;

  DLINK_FOREACH_SAFE(ptr, next_ptr, client_p->localClient->confs.head)
  {
    conf = ptr->data;

    if (type == CONF_TYPE || conf->type == type)
    {
      dlinkDelete(ptr, &client_p->localClient->confs);
      free_dlink_node(ptr);

      switch (conf->type)
      {
      case CLIENT_TYPE:
      case OPER_TYPE:
      case SERVER_TYPE:
        aconf = map_to_conf(conf);

        assert(aconf->clients > 0);

        if ((aclass_conf = ClassPtr(aconf)) != NULL)
        {
          aclass = map_to_conf(aclass_conf);

          assert(aclass->curr_user_count > 0);

          if (conf->type == CLIENT_TYPE)
            remove_from_cidr_check(&client_p->localClient->ip, aclass);
          if (--aclass->curr_user_count == 0 && aclass->active == 0)
            delete_conf_item(aclass_conf);
        }

        if (--aconf->clients == 0 && IsConfIllegal(aconf))
          delete_conf_item(conf);

        break;

      case LEAF_TYPE:
      case HUB_TYPE:
        match_item = map_to_conf(conf);
        if (match_item->ref_count == 0 && match_item->illegal)
          delete_conf_item(conf);
        break;
      default:
        break;
      }

      if (type != CONF_TYPE)
        return 0;
    }
  }

  return -1;
}
