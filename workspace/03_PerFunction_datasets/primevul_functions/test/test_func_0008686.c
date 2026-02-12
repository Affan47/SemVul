cupsdAddCert(int        pid,
             const char *username,
             int        type)
{
  int		i;
  cupsd_cert_t	*cert;
  int		fd;
  char		filename[1024];
  static const char hex[] = "0123456789ABCDEF";


  cupsdLogMessage(CUPSD_LOG_DEBUG, "cupsdAddCert: Adding certificate for PID %d", pid);


  if ((cert = calloc(sizeof(cupsd_cert_t), 1)) == NULL)
    return;


  cert->pid  = pid;
  cert->type = type;
  strlcpy(cert->username, username, sizeof(cert->username));

  for (i = 0; i < 32; i ++)
    cert->certificate[i] = hex[CUPS_RAND() & 15];


  snprintf(filename, sizeof(filename), "%s/certs/%d", StateDir, pid);
  unlink(filename);

  if ((fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0400)) < 0)
  {
    cupsdLogMessage(CUPSD_LOG_ERROR,
                    "Unable to create certificate file %s - %s",
                    filename, strerror(errno));
    free(cert);
    return;
  }

  if (pid == 0)
  {
#ifdef HAVE_ACL_INIT
    acl_t		acl;
    acl_entry_t		entry;
    acl_permset_t	permset;
#  ifdef HAVE_MBR_UID_TO_UUID
    uuid_t		group;
#  endif
    static int		acls_not_supported = 0;

#endif


    fchmod(fd, 0440);
    fchown(fd, RunUser, SystemGroupIDs[0]);

    cupsdLogMessage(CUPSD_LOG_DEBUG2, "cupsdAddCert: NumSystemGroups=%d", NumSystemGroups);

#ifdef HAVE_ACL_INIT
    if (NumSystemGroups > 1)
    {


      int	j;

#  ifdef HAVE_MBR_UID_TO_UUID


      acl = acl_init(NumSystemGroups - 1);

      for (i = 1; i < NumSystemGroups; i ++)
      {


        for (j = 0; j < i; j ++)
	  if (SystemGroupIDs[j] == SystemGroupIDs[i])
            break;

        if (j < i)
          continue;

        acl_create_entry(&acl, &entry);
	acl_get_permset(entry, &permset);
	acl_add_perm(permset, ACL_READ_DATA);
	acl_set_tag_type(entry, ACL_EXTENDED_ALLOW);
	mbr_gid_to_uuid((gid_t)SystemGroupIDs[i], group);
	acl_set_qualifier(entry, &group);
	acl_set_permset(entry, permset);
      }

#  else


      acl = acl_init(NumSystemGroups + 3);


      acl_create_entry(&acl, &entry);
      acl_get_permset(entry, &permset);
      acl_add_perm(permset, ACL_READ);
      acl_set_tag_type(entry, ACL_USER_OBJ);
      acl_set_permset(entry, permset);


      acl_create_entry(&acl, &entry);
      acl_get_permset(entry, &permset);
      acl_add_perm(permset, ACL_READ);
      acl_set_tag_type(entry, ACL_GROUP_OBJ);
      acl_set_permset(entry, permset);


      acl_create_entry(&acl, &entry);
      acl_get_permset(entry, &permset);
      acl_add_perm(permset, 0);
      acl_set_tag_type(entry, ACL_OTHER);
      acl_set_permset(entry, permset);


      acl_create_entry(&acl, &entry);
      acl_get_permset(entry, &permset);
      acl_add_perm(permset, ACL_READ);
      acl_set_tag_type(entry, ACL_MASK);
      acl_set_permset(entry, permset);

      for (i = 1; i < NumSystemGroups; i ++)
      {


        for (j = 0; j < i; j ++)
	  if (SystemGroupIDs[j] == SystemGroupIDs[i])
            break;

        if (j < i)
          continue;

        acl_create_entry(&acl, &entry);
	acl_get_permset(entry, &permset);
	acl_add_perm(permset, ACL_READ);
	acl_set_tag_type(entry, ACL_GROUP);
	acl_set_qualifier(entry, SystemGroupIDs + i);
	acl_set_permset(entry, permset);
      }

      if (acl_valid(acl))
      {
        char *text, *textptr;

        cupsdLogMessage(CUPSD_LOG_ERROR, "ACL did not validate: %s",
	                strerror(errno));
        text = acl_to_text(acl, NULL);
	for (textptr = strchr(text, '\n');
	     textptr;
	     textptr = strchr(textptr + 1, '\n'))
	  *textptr = ',';

	cupsdLogMessage(CUPSD_LOG_ERROR, "ACL: %s", text);
	acl_free(text);
      }
#  endif

      if (acl_set_fd(fd, acl))
      {
	if (errno != EOPNOTSUPP || !acls_not_supported)
	  cupsdLogMessage(CUPSD_LOG_ERROR,
			  "Unable to set ACLs on root certificate \"%s\" - %s",
			  filename, strerror(errno));

	if (errno == EOPNOTSUPP)
	  acls_not_supported = 1;
      }

      acl_free(acl);
    }
#endif

    RootCertTime = time(NULL);
  }
  else
  {


    fchmod(fd, 0400);
    fchown(fd, User, Group);
  }

  write(fd, cert->certificate, strlen(cert->certificate));
  close(fd);


  cert->next = Certs;
  Certs      = cert;
}
