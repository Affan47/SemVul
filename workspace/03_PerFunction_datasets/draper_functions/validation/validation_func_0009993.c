evd_service_validate_tls_connection (EvdService *self, EvdConnection *conn)
{
  EvdServiceValidate ret = EVD_SERVICE_VALIDATE_ACCEPT;


  if (ret == EVD_SERVICE_VALIDATE_ACCEPT)
    {
      evd_service_accept_connection_priv (self, conn);
    }
  else if (ret == EVD_SERVICE_VALIDATE_REJECT)
    {

    }
  else
    {


    }
}
