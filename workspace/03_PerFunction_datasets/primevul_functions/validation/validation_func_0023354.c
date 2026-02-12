JNIEXPORT void JNICALL Java_edu_berkeley_cs_rise_opaque_execution_SGXEnclave_RemoteAttestation3(
    JNIEnv *env, jobject obj,
    jlong eid,
    jbyteArray att_result_input) {

  (void)env;
  (void)obj;

#ifdef DEBUG
  printf("RemoteAttestation3 called\n");
#endif

  sgx_status_t status = SGX_SUCCESS;

  jboolean if_copy = false;
  jbyte *ptr = env->GetByteArrayElements(att_result_input, &if_copy);

  ra_samp_response_header_t *att_result_full = (ra_samp_response_header_t *)(ptr);
  sample_ra_att_result_msg_t *att_result = (sample_ra_att_result_msg_t *) att_result_full->body;

#ifdef DEBUG
  printf("[RemoteAttestation3] att_result's size is %u\n", att_result_full->size);
#endif


  int ret = 0;
  ret = ecall_verify_att_result_mac(eid,
                                    &status,
                                    context,
                                    (uint8_t*)&att_result->platform_info_blob,
                                    sizeof(ias_platform_info_blob_t),
                                    (uint8_t*)&att_result->mac,
                                    sizeof(sgx_mac_t));

  if((SGX_SUCCESS != ret) || (SGX_SUCCESS != status)) {
    fprintf(stdout, "\nError: INTEGRITY FAILED - attestation result message MK based cmac failed in [%s], status is %u", __FUNCTION__, (uint32_t) status);
    return ;
  }

  bool attestation_passed = true;


  if (0 != att_result_full->status[0] || 0 != att_result_full->status[1]) {
    fprintf(stdout, "\nError, attestation result message MK based cmac "
            "failed in [%s].", __FUNCTION__);
    attestation_passed = false;
  }


#ifdef DEBUG
  printf("[RemoteAttestation3] %u\n", attestation_passed);
#endif
  if (attestation_passed) {
    ret = ecall_put_secret_data(eid,
                                &status,
                                context,
                                att_result->secret.payload,
                                att_result->secret.payload_size,
                                att_result->secret.payload_tag);

    if((SGX_SUCCESS != ret)  || (SGX_SUCCESS != status)) {
      fprintf(stdout, "\nError, attestation result message secret "
              "using SK based AESGCM failed in [%s]. ret = "
              "0x%0x. status = 0x%0x", __FUNCTION__, ret,
              status);
      return ;
    }
  }

  fprintf(stdout, "\nSecret successfully received from server.");
  fprintf(stdout, "\nRemote attestation success!\n");

#ifdef DEBUG
  fprintf(stdout, "Destroying the key exchange context\n");
#endif
  ecall_enclave_ra_close(eid, context);
}
