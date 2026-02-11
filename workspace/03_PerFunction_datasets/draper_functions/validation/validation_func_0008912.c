gnutls_x509_crq_import (gnutls_x509_crq_t crq,
                        const gnutls_datum_t * data,
                        gnutls_x509_crt_fmt_t format)
{
  int result = 0, need_free = 0;
  gnutls_datum_t _data;

  if (crq == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  _data.data = data->data;
  _data.size = data->size;


  if (format == GNUTLS_X509_FMT_PEM)
    {
      opaque *out;


      result = _gnutls_fbase64_decode (PEM_CRQ, data->data, data->size, &out);

      if (result <= 0)
        result =
          _gnutls_fbase64_decode (PEM_CRQ2, data->data, data->size, &out);

      if (result <= 0)
        {
          if (result == 0)
            result = GNUTLS_E_INTERNAL_ERROR;
          gnutls_assert ();
          return result;
        }

      _data.data = out;
      _data.size = result;

      need_free = 1;
    }

  result = asn1_der_decoding (&crq->crq, _data.data, _data.size, NULL);
  if (result != ASN1_SUCCESS)
    {
      result = _gnutls_asn2err (result);
      gnutls_assert ();
      goto cleanup;
    }

  result = 0;

cleanup:
  if (need_free)
    _gnutls_free_datum (&_data);
  return result;
}
