consensus_method_is_supported(int method)
{
  if (method == MIN_METHOD_FOR_ED25519_ID_IN_MD) {


    return 0;
  }

  return (method >= MIN_SUPPORTED_CONSENSUS_METHOD) &&
    (method <= MAX_SUPPORTED_CONSENSUS_METHOD);
}
