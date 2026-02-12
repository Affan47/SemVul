findugid(address_item *addr, transport_instance *tp, uid_t *uidp, gid_t *gidp,
  BOOL *igfp)
{
uschar *nuname;
BOOL gid_set = FALSE;


*igfp = tp->initgroups;


if (tp->gid_set)
  {
  *gidp = tp->gid;
  gid_set = TRUE;
  }
else if (tp->expand_gid)
  {
  if (!route_find_expanded_group(tp->expand_gid, tp->name, US"transport", gidp,
    &(addr->message)))
    {
    common_error(FALSE, addr, ERRNO_GIDFAIL, NULL);
    return FALSE;
    }
  gid_set = TRUE;
  }


if (!gid_set && testflag(addr, af_gid_set))
  {
  *gidp = addr->gid;
  gid_set = TRUE;
  }


if (tp->uid_set) *uidp = tp->uid;


else if (tp->expand_uid)
  {
  struct passwd *pw;
  if (!route_find_expanded_user(tp->expand_uid, tp->name, US"transport", &pw,
       uidp, &(addr->message)))
    {
    common_error(FALSE, addr, ERRNO_UIDFAIL, NULL);
    return FALSE;
    }
  if (!gid_set && pw)
    {
    *gidp = pw->pw_gid;
    gid_set = TRUE;
    }
  }


else if (tp->deliver_as_creator)
  {
  *uidp = originator_uid;
  if (!gid_set)
    {
    *gidp = originator_gid;
    gid_set = TRUE;
    }
  }


else if (testflag(addr, af_uid_set))
  {
  *uidp = addr->uid;
  *igfp = testflag(addr, af_initgroups);
  }


else
  {
  *uidp = exim_uid;
  if (!gid_set)
    {
    *gidp = exim_gid;
    gid_set = TRUE;
    }
  }


if (!gid_set)
  {
  common_error(TRUE, addr, ERRNO_GIDFAIL, US"User set without group for "
    "%s transport", tp->name);
  return FALSE;
  }


nuname = check_never_users(*uidp, never_users)
  ? US"never_users"
  : check_never_users(*uidp, fixed_never_users)
  ? US"fixed_never_users"
  : NULL;
if (nuname)
  {
  common_error(TRUE, addr, ERRNO_UIDFAIL, US"User %ld set for %s transport "
    "is on the %s list", (long int)(*uidp), tp->name, nuname);
  return FALSE;
  }


return TRUE;
}
