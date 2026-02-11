node_id_dump(const node_id_t *id)
{
  gchar *msg;
  g_assert(id);
  switch (id->node_type)
    {
    case APEMODE_DEFAULT:
      msg = g_strdup_printf("NONE: 00:00:00:00:00:00");
      break;
    case LINK6:
      msg = g_strdup_printf("LINK: %s", ether_to_str(id->addr.eth));
      break;
    case IP:
      msg = g_strdup_printf("%s: %s", type_to_str (&id->addr.ip),
                            address_to_str (&id->addr.ip));
      break;
    case TCP:
      msg = g_strdup_printf("TCP/UDP: %s:%u",
                            address_to_str (&id->addr.tcp4.host),
                            id->addr.tcp4.port);
      break;
    default:
      msg = g_strdup_printf("node_id_type %d unknown", (int)(id->node_type));
      break;
    }

  return msg;
}
