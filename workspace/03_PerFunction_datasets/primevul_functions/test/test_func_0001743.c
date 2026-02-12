xauth_entry_should_propagate (Xauth *xa,
                              char  *hostname,
                              char  *number)
{

  if (xa->family != FamilyLocal && xa->family != FamilyWild)
    return FALSE;


  if (xa->family == FamilyLocal && !auth_streq (hostname, xa->address, xa->address_length))
    {


      const char *xauth_local_hostname;
      xauth_local_hostname = g_getenv ("XAUTHLOCALHOSTNAME");
      if (xauth_local_hostname == NULL)
        return FALSE;

      if (!auth_streq ((char *) xauth_local_hostname, xa->address, xa->address_length))
        return FALSE;
    }


  if (xa->number != NULL && !auth_streq (number, xa->number, xa->number_length))
    return FALSE;

  return TRUE;
}
