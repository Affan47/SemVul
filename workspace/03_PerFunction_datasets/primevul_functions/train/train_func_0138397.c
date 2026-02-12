_gnutls_x509_crt_check_revocation(gnutls_x509_crt_t cert,
				  const gnutls_x509_crl_t * crl_list,
				  int crl_list_length,
				  gnutls_verify_output_function func)
{
	uint8_t serial[128];
	uint8_t cert_serial[128];
	size_t serial_size, cert_serial_size;
	int ret, j;
	gnutls_x509_crl_iter_t iter = NULL;

	if (cert == NULL) {
		gnutls_assert();
		return GNUTLS_E_INVALID_REQUEST;
	}

	for (j = 0; j < crl_list_length; j++) {


		ret = crl_issuer_matches(crl_list[j], cert);
		if (ret == 0) {


			gnutls_assert();
			continue;
		}


		cert_serial_size = sizeof(cert_serial);
		ret =
		    gnutls_x509_crt_get_serial(cert, cert_serial,
					       &cert_serial_size);
		if (ret < 0) {
			gnutls_assert();
			return ret;
		}


		iter = NULL;
		do {
			serial_size = sizeof(serial);
			ret =
			    gnutls_x509_crl_iter_crt_serial(crl_list[j],
							    &iter,
							    serial,
							    &serial_size,
							    NULL);
			if (ret == GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE) {
				break;
			} else if (ret < 0) {
				gnutls_assert();
				goto fail;
			}

			if (serial_size == cert_serial_size) {
				if (memcmp
				    (serial, cert_serial,
				     serial_size) == 0) {

					if (func)
						func(cert, NULL,
						     crl_list[j],
						     GNUTLS_CERT_REVOKED |
						     GNUTLS_CERT_INVALID);
					ret = 1;
					goto fail;
				}
			}
		} while(1);

		gnutls_x509_crl_iter_deinit(iter);
		iter = NULL;

		if (func)
			func(cert, NULL, crl_list[j], 0);

	}
	return 0;

 fail:
 	gnutls_x509_crl_iter_deinit(iter);
 	return ret;
}
