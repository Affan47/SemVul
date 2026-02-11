NSSCKFWC_CloseSession
(
  NSSCKFWInstance *fwInstance,
  CK_SESSION_HANDLE hSession
)
{
  CK_RV error = CKR_OK;
  NSSCKFWSession *fwSession;

  if (!fwInstance) {
    error = CKR_CRYPTOKI_NOT_INITIALIZED;
    goto loser;
  }

  fwSession = nssCKFWInstance_ResolveSessionHandle(fwInstance, hSession);
  if (!fwSession) {
    error = CKR_SESSION_HANDLE_INVALID;
    goto loser;
  }

  nssCKFWInstance_DestroySessionHandle(fwInstance, hSession);
  error = nssCKFWSession_Destroy(fwSession, CK_TRUE);

  if( CKR_OK != error ) {
    goto loser;
  }

  return CKR_OK;

 loser:
  switch( error ) {
  case CKR_SESSION_CLOSED:

    break;
  case CKR_DEVICE_REMOVED:

    break;
  case CKR_CRYPTOKI_NOT_INITIALIZED:
  case CKR_DEVICE_ERROR:
  case CKR_DEVICE_MEMORY:
  case CKR_FUNCTION_FAILED:
  case CKR_GENERAL_ERROR:
  case CKR_HOST_MEMORY:
  case CKR_SESSION_HANDLE_INVALID:
    break;
  default:
  case CKR_OK:
    error = CKR_GENERAL_ERROR;
    break;
  }

  return error;
}
