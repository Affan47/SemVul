krb5_gss_register_acceptor_identity(const char *keytab)
{
    static const gss_OID_desc req_oid = {
        GSS_KRB5_REGISTER_ACCEPTOR_IDENTITY_OID_LENGTH,
        GSS_KRB5_REGISTER_ACCEPTOR_IDENTITY_OID };
    OM_uint32 major_status;
    OM_uint32 minor_status;
    gss_buffer_desc req_buffer;

    req_buffer.length = (keytab == NULL) ? 0 : strlen(keytab);
    req_buffer.value = (char *)keytab;

    major_status = gssspi_mech_invoke(&minor_status,
                                      (gss_OID)gss_mech_krb5,
                                      (gss_OID)&req_oid,
                                      &req_buffer);

    return major_status;
}
