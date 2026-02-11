nssCKFWCryptoOperation_GetOperationLength
(
  NSSCKFWCryptoOperation *fwOperation,
  NSSItem *inputBuffer,
  CK_RV *pError
)
{
  if (!fwOperation->mdOperation->GetOperationLength) {
    *pError = CKR_FUNCTION_FAILED;
    return 0;
  }
  return fwOperation->mdOperation->GetOperationLength(
                fwOperation->mdOperation,
                fwOperation,
                fwOperation->mdSession,
                fwOperation->fwSession,
                fwOperation->mdToken,
                fwOperation->fwToken,
                fwOperation->mdInstance,
                fwOperation->fwInstance,
                inputBuffer,
                pError);
}
