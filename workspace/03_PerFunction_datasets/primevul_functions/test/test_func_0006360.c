TEST_P(SslSocketTest, RevokedLeafCertificateOnlyLeafCRLValidation) {


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
      only_verify_leaf_cert_crl: true
)EOF";


  const std::string revoked_client_ctx_yaml = R"EOF(
  common_tls_context:
    tls_certificates:
      certificate_chain:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns3_cert.pem"
      private_key:
        filename: "{{ test_rundir }}/test/extensions/transport_sockets/tls/test_data/san_dns3_key.pem"
)EOF";

  TestUtilOptions complete_revoked_test_options(revoked_client_ctx_yaml, incomplete_server_ctx_yaml,
                                                false, GetParam());
  testUtil(complete_revoked_test_options.setExpectedServerStats("ssl.fail_verify_error")
               .setExpectedVerifyErrorCode(X509_V_ERR_CERT_REVOKED));
}
