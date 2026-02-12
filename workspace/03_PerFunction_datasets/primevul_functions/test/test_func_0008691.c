cupsdDeleteCert(int pid)
{
  cupsd_cert_t	*cert,
		*prev;
  char		filename[1024];


  for (prev = NULL, cert = Certs; cert != NULL; prev = cert, cert = cert->next)
    if (cert->pid == pid)
    {


      cupsdLogMessage(CUPSD_LOG_DEBUG2, "cupsdDeleteCert: Removing certificate for PID %d.", pid);

      if (prev == NULL)
        Certs = cert->next;
      else
        prev->next = cert->next;

      free(cert);


      snprintf(filename, sizeof(filename), "%s/certs/%d", StateDir, pid);
      if (unlink(filename))
	cupsdLogMessage(CUPSD_LOG_ERROR, "Unable to remove %s!", filename);

      return;
    }
}
