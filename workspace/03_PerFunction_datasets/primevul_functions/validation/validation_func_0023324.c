JNIEXPORT jbyteArray JNICALL Java_edu_berkeley_cs_rise_opaque_execution_SGXEnclave_RemoteAttestation1(
    JNIEnv *env, jobject obj,
    jlong eid) {

  (void)env;
  (void)obj;
  (void)eid;


  int ret = 0;
  int enclave_lost_retry_time = 2;
  sgx_status_t status;


  do {
    ret = ecall_enclave_init_ra(eid,
                                &status,
                                false,
                                &context);
  } while (SGX_ERROR_ENCLAVE_LOST == ret && enclave_lost_retry_time--);

  if (status != SGX_SUCCESS) {
    printf("[RemoteAttestation1] enclave_init_ra's status is %u\n", (uint32_t) status);
    std::exit(1);
  }

  uint8_t *msg1 = (uint8_t *) malloc(sizeof(sgx_ra_msg1_t));

#ifdef DEBUG
  printf("[RemoteAttestation1] context is %u, eid: %u\n", (uint32_t) context, (uint32_t) eid);
#endif

  ret = sgx_ra_get_msg1(context, eid, sgx_ra_get_ga, (sgx_ra_msg1_t*) msg1);

  if(SGX_SUCCESS != ret) {
    ret = -1;
    fprintf(stdout, "\nError, call sgx_ra_get_msg1 fail [%s].", __FUNCTION__);
    jbyteArray array_ret = env->NewByteArray(0);
    return array_ret;
  } else {
#ifdef DEBUG
    fprintf(stdout, "\nCall sgx_ra_get_msg1 success.\n");
    fprintf(stdout, "\nMSG1 body generated -\n");
    PRINT_BYTE_ARRAY(stdout, msg1, sizeof(sgx_ra_msg1_t));
#endif
  }


#ifdef DEBUG
  fprintf(stdout, "\nSending msg1 to remote attestation service provider."
          "Expecting msg2 back.\n");
#endif

  jbyteArray array_ret = env->NewByteArray(sizeof(sgx_ra_msg1_t));
  env->SetByteArrayRegion(array_ret, 0, sizeof(sgx_ra_msg1_t), (jbyte *) msg1);

  free(msg1);

  return array_ret;
}
