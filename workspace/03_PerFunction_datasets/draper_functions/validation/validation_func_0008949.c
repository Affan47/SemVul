krb5_unpack_full_ipaddr(krb5_context context, const krb5_address *inaddr, krb5_int32 *adr, krb5_int16 *port)
{
    unsigned long smushaddr;
    unsigned short smushport;
    register krb5_octet *marshal;
    krb5_addrtype temptype;
    krb5_ui_4 templength;

    if (inaddr->addrtype != ADDRTYPE_ADDRPORT)
        return KRB5_PROG_ATYPE_NOSUPP;

    if (inaddr->length != sizeof(smushaddr)+ sizeof(smushport) +
        2*sizeof(temptype) + 2*sizeof(templength))
        return KRB5_PROG_ATYPE_NOSUPP;

    marshal = inaddr->contents;

    (void) memcpy(&temptype, marshal, sizeof(temptype));
    marshal += sizeof(temptype);
    if (temptype != htons(ADDRTYPE_INET))
        return KRB5_PROG_ATYPE_NOSUPP;

    (void) memcpy(&templength, marshal, sizeof(templength));
    marshal += sizeof(templength);
    if (templength != htonl(sizeof(smushaddr)))
        return KRB5_PROG_ATYPE_NOSUPP;

    (void) memcpy(&smushaddr, marshal, sizeof(smushaddr));

    marshal += sizeof(smushaddr);

    (void) memcpy(&temptype, marshal, sizeof(temptype));
    marshal += sizeof(temptype);
    if (temptype != htons(ADDRTYPE_IPPORT))
        return KRB5_PROG_ATYPE_NOSUPP;

    (void) memcpy(&templength, marshal, sizeof(templength));
    marshal += sizeof(templength);
    if (templength != htonl(sizeof(smushport)))
        return KRB5_PROG_ATYPE_NOSUPP;

    (void) memcpy(&smushport, marshal, sizeof(smushport));


    *adr = (krb5_int32) smushaddr;
    *port = (krb5_int16) smushport;
    return 0;
}
