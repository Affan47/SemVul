nssCKFWCryptoOperation_GetFinalLength
(
  NSSCKFWCryptoOperation *fwOperation,
  CK_RV *pError
)
{
  if (!fwOperation->mdOperation->GetFinalLength) {
    *pError = CKR_FUNCTION_FAILED;
    return 0;
  }
  return fwOperation->mdOperation->GetFinalLength(
                fwOperation->mdOperation,
                fwOperation,
                fwOperation->mdSession,
                fwOperation->fwSession,
                fwOperation->mdToken,
                fwOperation->fwToken,
                fwOperation->mdInstance,
                fwOperation->fwInstance,
                pError);
}
