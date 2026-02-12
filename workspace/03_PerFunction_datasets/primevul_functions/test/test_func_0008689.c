cupsdDeleteAllCerts(void)
{
  cupsd_cert_t	*cert,
		*next;
  char		filename[1024];


  for (cert = Certs; cert != NULL; cert = next)
  {


    snprintf(filename, sizeof(filename), "%s/certs/%d", StateDir, cert->pid);
    if (unlink(filename))
      cupsdLogMessage(CUPSD_LOG_ERROR, "Unable to remove %s!", filename);


    next = cert->next;
    free(cert);
  }

  Certs        = NULL;
  RootCertTime = 0;
}
