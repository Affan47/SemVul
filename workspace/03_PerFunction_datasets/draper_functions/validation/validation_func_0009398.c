radius_authenticate_pdu(RADIUS_PDU *pdu, Octstr **data, Octstr *secret)
{
    int rc = 0;
    Octstr *stream;
    Octstr *attributes;
    Octstr *digest;

    stream = attributes = digest = NULL;


    if (octstr_len(*data) > 20)
        attributes = octstr_copy(*data, 20, octstr_len(*data)-20);

    switch (pdu->type) {
        case 0x04:
            stream = octstr_copy(*data, 0, 4);
            octstr_append_data(stream, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
            octstr_append(stream, attributes);
            octstr_append(stream, secret);
            digest = md5(stream);
            rc = octstr_compare(pdu->u.Accounting_Request.authenticator,
                                digest) == 0 ? 1 : 0;
            break;
        case 0x05:
            stream = octstr_duplicate(*data);
            octstr_append(stream, secret);
            digest = md5(stream);
            octstr_delete(*data, 4, 16);
            octstr_insert(*data, digest, 4);
            break;
        default:
            break;
    }

    octstr_destroy(attributes);
    octstr_destroy(stream);
    octstr_destroy(digest);

    return rc;
}
