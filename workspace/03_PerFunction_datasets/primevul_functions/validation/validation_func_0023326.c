JNIEXPORT jbyteArray JNICALL Java_edu_berkeley_cs_rise_opaque_execution_SGXEnclave_RemoteAttestation0(
  JNIEnv *env, jobject obj) {

  (void)env;
  (void)obj;


  int ret = 0;


  uint32_t extended_epid_group_id = 0;
  ret = sgx_get_extended_epid_group_id(&extended_epid_group_id);
  if (SGX_SUCCESS != (sgx_status_t)ret) {
    fprintf(stdout, "\nError, call sgx_get_extended_epid_group_id fail [%s].", __FUNCTION__);
    jbyteArray array_ret = env->NewByteArray(0);
    return array_ret;
  }

#ifdef DEBUG
  fprintf(stdout, "\nCall sgx_get_extended_epid_group_id success.");
#endif


#ifdef DEBUG
  fprintf(stdout, "\nSending msg0 to remote attestation service provider.\n");
#endif

  jbyteArray array_ret = env->NewByteArray(sizeof(uint32_t));
  env->SetByteArrayRegion(array_ret, 0, sizeof(uint32_t), (jbyte *) &extended_epid_group_id);

  return array_ret;
}
