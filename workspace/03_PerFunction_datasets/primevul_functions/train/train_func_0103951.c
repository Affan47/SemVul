ospf_make_auth (struct ospf_interface *oi, struct ospf_header *ospfh)
{
  struct crypt_key *ck;

  switch (ospf_auth_type (oi))
    {
    case OSPF_AUTH_NULL:

      break;
    case OSPF_AUTH_SIMPLE:
      memcpy (ospfh->u.auth_data, OSPF_IF_PARAM (oi, auth_simple),
	      OSPF_AUTH_SIMPLE_SIZE);
      break;
    case OSPF_AUTH_CRYPTOGRAPHIC:

      if (list_isempty (OSPF_IF_PARAM (oi, auth_crypt)))
	{
	  ospfh->u.crypt.zero = 0;
	  ospfh->u.crypt.key_id = 0;
	  ospfh->u.crypt.auth_data_len = OSPF_AUTH_MD5_SIZE;
	}
      else
	{
	  ck = listgetdata (listtail(OSPF_IF_PARAM (oi, auth_crypt)));
	  ospfh->u.crypt.zero = 0;
	  ospfh->u.crypt.key_id = ck->key_id;
	  ospfh->u.crypt.auth_data_len = OSPF_AUTH_MD5_SIZE;
	}

      break;
    default:

      break;
    }

  return 0;
}
