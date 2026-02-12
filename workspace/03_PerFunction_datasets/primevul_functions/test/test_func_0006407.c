TEST_P(SslSocketTest, RevokedIntermediateCertificateCRLInTrustedCA) {


  const std::string complete_server_ctx_yaml = R"EOF(
  common_tls_context:
    tls_certificates:
      certificate_chain:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/unittest_cert.pem"
      private_key:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/unittest_key.pem"
    validation_context:
      trusted_ca:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/intermediate_ca_cert_chain_with_crl_chain.pem"
)EOF";


  const std::string incomplete_server_ctx_yaml = R"EOF(
  common_tls_context:
    tls_certificates:
      certificate_chain:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/unittest_cert.pem"
      private_key:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/unittest_key.pem"
    validation_context:
      trusted_ca:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/intermediate_ca_cert_chain_with_crl.pem"
)EOF";


  const std::string revoked_client_ctx_yaml = R"EOF(
  common_tls_context:
    tls_certificates:
      certificate_chain:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns3_cert.pem"
      private_key:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns3_key.pem"
)EOF";


  const std::string unrevoked_client_ctx_yaml = R"EOF(
  common_tls_context:
    tls_certificates:
      certificate_chain:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns4_cert.pem"
      private_key:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns4_key.pem"
)EOF";


  TestUtilOptions incomplete_revoked_test_options(revoked_client_ctx_yaml,
                                                  incomplete_server_ctx_yaml, false, GetParam());
  testUtil(incomplete_revoked_test_options.setExpectedServerStats("ssl.fail_verify_error")
               .setExpectedVerifyErrorCode(X509_V_ERR_CERT_REVOKED));


  TestUtilOptions incomplete_unrevoked_test_options(unrevoked_client_ctx_yaml,
                                                    incomplete_server_ctx_yaml, false, GetParam());
  testUtil(incomplete_unrevoked_test_options.setExpectedServerStats("ssl.fail_verify_error")
               .setExpectedVerifyErrorCode(X509_V_ERR_UNABLE_TO_GET_CRL));


  TestUtilOptions complete_revoked_test_options(revoked_client_ctx_yaml, complete_server_ctx_yaml,
                                                false, GetParam());
  testUtil(complete_revoked_test_options.setExpectedServerStats("ssl.fail_verify_error")
               .setExpectedVerifyErrorCode(X509_V_ERR_CERT_REVOKED));


  TestUtilOptions complete_unrevoked_test_options(unrevoked_client_ctx_yaml,
                                                  complete_server_ctx_yaml, true, GetParam());
  testUtil(complete_unrevoked_test_options.setExpectedSerialNumber(TEST_SAN_DNS4_CERT_SERIAL));
}
