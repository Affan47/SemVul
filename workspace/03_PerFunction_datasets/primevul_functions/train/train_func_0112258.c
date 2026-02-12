usm_rgenerate_out_msg(int msgProcModel,
                      u_char * globalData,


                      size_t globalDataLen,
                      int maxMsgSize,
                      int secModel,
                      u_char * secEngineID,
                      size_t secEngineIDLen,
                      char *secName,
                      size_t secNameLen,
                      int secLevel,
                      u_char * scopedPdu,


                      size_t scopedPduLen,
                      void *secStateRef,


                      u_char ** wholeMsg,


                      size_t * wholeMsgLen,


                      size_t * offset


    )
{
    size_t          msgAuthParmLen = 0;
    u_int           boots_uint;
    u_int           time_uint;
    long            boots_long;
    long            time_long;


    char           *theName = NULL;
    u_int           theNameLength = 0;
    u_char         *theEngineID = NULL;
    u_int           theEngineIDLength = 0;
    u_char         *theAuthKey = NULL;
    u_int           theAuthKeyLength = 0;
    const oid      *theAuthProtocol = NULL;
    u_int           theAuthProtocolLength = 0;
    u_char         *thePrivKey = NULL;
    u_int           thePrivKeyLength = 0;
    const oid      *thePrivProtocol = NULL;
    u_int           thePrivProtocolLength = 0;
    int             theSecLevel = 0;

    size_t          salt_length = 0, save_salt_length = 0;
    u_char          salt[BYTESIZE(USM_MAX_SALT_LENGTH)];
    u_char          authParams[USM_MAX_AUTHSIZE];
    u_char          iv[BYTESIZE(USM_MAX_SALT_LENGTH)];
    size_t          sp_offset = 0, mac_offset = 0;
    int             rc = 0;

    DEBUGMSGTL(("usm", "USM processing has begun (offset %d)\n", (int)*offset));

    if (secStateRef != NULL) {


        struct usmStateReference *ref
            = (struct usmStateReference *) secStateRef;

        theName = ref->usr_name;
        theNameLength = ref->usr_name_length;
        theEngineID = ref->usr_engine_id;
        theEngineIDLength = ref->usr_engine_id_length;

        if (!theEngineIDLength) {
            theEngineID = secEngineID;
            theEngineIDLength = secEngineIDLen;
        }

        theAuthProtocol = ref->usr_auth_protocol;
        theAuthProtocolLength = ref->usr_auth_protocol_length;
        theAuthKey = ref->usr_auth_key;
        theAuthKeyLength = ref->usr_auth_key_length;
        thePrivProtocol = ref->usr_priv_protocol;
        thePrivProtocolLength = ref->usr_priv_protocol_length;
        thePrivKey = ref->usr_priv_key;
        thePrivKeyLength = ref->usr_priv_key_length;
        theSecLevel = ref->usr_sec_level;
    }


    else {
        struct usmUser *user;


        if ((user = usm_get_user(secEngineID, secEngineIDLen, secName))
            == NULL && secLevel != SNMP_SEC_LEVEL_NOAUTH) {
            DEBUGMSGTL(("usm", "Unknown User\n"));
            return SNMPERR_USM_UNKNOWNSECURITYNAME;
        }

        theName = secName;
        theNameLength = secNameLen;
        theEngineID = secEngineID;
        theSecLevel = secLevel;
        theEngineIDLength = secEngineIDLen;
        if (user) {
            theAuthProtocol = user->authProtocol;
            theAuthProtocolLength = user->authProtocolLen;
            theAuthKey = user->authKey;
            theAuthKeyLength = user->authKeyLen;
            thePrivProtocol = user->privProtocol;
            thePrivProtocolLength = user->privProtocolLen;
            thePrivKey = user->privKey;
            thePrivKeyLength = user->privKeyLen;
        } else {


            theAuthProtocol = usmNoAuthProtocol;
            theAuthProtocolLength =
                sizeof(usmNoAuthProtocol) / sizeof(oid);
            theAuthKey = NULL;
            theAuthKeyLength = 0;
            thePrivProtocol = usmNoPrivProtocol;
            thePrivProtocolLength =
                sizeof(usmNoPrivProtocol) / sizeof(oid);
            thePrivKey = NULL;
            thePrivKeyLength = 0;
        }
    }


    if (usm_check_secLevel_vs_protocols(theSecLevel,
                                        theAuthProtocol,
                                        theAuthProtocolLength,
                                        thePrivProtocol,
                                        thePrivProtocolLength) == 1) {
        DEBUGMSGTL(("usm", "Unsupported Security Level or type (%d)\n",
                    theSecLevel));

        return SNMPERR_USM_UNSUPPORTEDSECURITYLEVEL;
    }


    if (get_enginetime(theEngineID, theEngineIDLength,
                       &boots_uint, &time_uint, FALSE) == -1) {
        DEBUGMSGTL(("usm", "%s\n", "Failed to find engine data."));
    }

    boots_long = boots_uint;
    time_long = time_uint;

    if (theSecLevel == SNMP_SEC_LEVEL_AUTHPRIV) {


        u_char         *ciphertext = NULL;
        size_t          ciphertextlen = scopedPduLen + 64;
        int             priv_type = sc_get_privtype(thePrivProtocol,
                                                    thePrivProtocolLength);

        if ((ciphertext = (u_char *) malloc(ciphertextlen)) == NULL) {
            DEBUGMSGTL(("usm",
                        "couldn't malloc %d bytes for encrypted PDU\n",
                        (int)ciphertextlen));
            return SNMPERR_MALLOC;
        }


#ifdef HAVE_AES
        if (USM_CREATE_USER_PRIV_AES == (priv_type & USM_PRIV_MASK_ALG)) {
            salt_length = BYTESIZE(USM_AES_SALT_LENGTH);
            save_salt_length = BYTESIZE(USM_AES_SALT_LENGTH)/2;
            if (!thePrivKey ||
                usm_set_aes_iv(salt, &salt_length,
                               htonl(boots_uint), htonl(time_uint),
                               iv) == -1) {
                DEBUGMSGTL(("usm", "Can't set AES iv.\n"));
                SNMP_FREE(ciphertext);
                return SNMPERR_USM_GENERICERROR;
            }
        }
#endif
#ifndef NETSNMP_DISABLE_DES
        if (USM_CREATE_USER_PRIV_DES == (priv_type & USM_PRIV_MASK_ALG)) {
            salt_length = BYTESIZE(USM_DES_SALT_LENGTH);
            save_salt_length = BYTESIZE(USM_DES_SALT_LENGTH);
            if (!thePrivKey || (usm_set_salt(salt, &salt_length,
                                             thePrivKey + 8,
                                             thePrivKeyLength - 8,
                                             iv) == -1)) {
                DEBUGMSGTL(("usm", "Can't set DES-CBC salt.\n"));
                SNMP_FREE(ciphertext);
                return SNMPERR_USM_GENERICERROR;
            }
        }
#endif
#ifdef NETSNMP_ENABLE_TESTING_CODE
        if (debug_is_token_registered("usm/dump") == SNMPERR_SUCCESS) {
            dump_chunk("usm/dump", "This data was encrypted:",
                       scopedPdu, scopedPduLen);
        }
#endif

        if (sc_encrypt(thePrivProtocol, thePrivProtocolLength,
                       thePrivKey, thePrivKeyLength,
                       salt, salt_length,
                       scopedPdu, scopedPduLen,
                       ciphertext, &ciphertextlen) != SNMP_ERR_NOERROR) {
            DEBUGMSGTL(("usm", "encryption error.\n"));
            SNMP_FREE(ciphertext);
            return SNMPERR_USM_ENCRYPTIONERROR;
        }


        *offset = 0;
        rc = asn_realloc_rbuild_string(wholeMsg, wholeMsgLen, offset, 1,
                                       (u_char) (ASN_UNIVERSAL |
                                                 ASN_PRIMITIVE |
                                                 ASN_OCTET_STR),
                                       ciphertext, ciphertextlen);
        if (rc == 0) {
            DEBUGMSGTL(("usm", "Encryption failed.\n"));
            SNMP_FREE(ciphertext);
            return SNMPERR_USM_ENCRYPTIONERROR;
        }

#ifdef NETSNMP_ENABLE_TESTING_CODE
        if (debug_is_token_registered("usm/dump") == SNMPERR_SUCCESS) {
            dump_chunk("usm/dump", "salt + Encrypted form: ", salt,
                       salt_length);
            dump_chunk("usm/dump", "wholeMsg:",
                       (*wholeMsg + *wholeMsgLen - *offset), *offset);
        }
#endif

        DEBUGMSGTL(("usm", "Encryption successful.\n"));
        SNMP_FREE(ciphertext);
    } else {


    }


    sp_offset = *offset;

    DEBUGDUMPHEADER("send", "msgPrivacyParameters");


    rc = asn_realloc_rbuild_string(wholeMsg, wholeMsgLen, offset, 1,
                                   (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE
                                             | ASN_OCTET_STR),
                                   iv,
                                   save_salt_length);
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building privParams failed.\n"));
        return SNMPERR_TOO_LONG;
    }

    DEBUGDUMPHEADER("send", "msgAuthenticationParameters");


    if (theSecLevel == SNMP_SEC_LEVEL_AUTHNOPRIV
        || theSecLevel == SNMP_SEC_LEVEL_AUTHPRIV) {
        memset(authParams, 0, sizeof(authParams));
        msgAuthParmLen =
            sc_get_auth_maclen(sc_get_authtype(theAuthProtocol,
                                               theAuthProtocolLength));
    }

    rc = asn_realloc_rbuild_string(wholeMsg, wholeMsgLen, offset, 1,
                                   (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE
                                             | ASN_OCTET_STR), authParams,
                                   msgAuthParmLen);
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building authParams failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    mac_offset = *offset - 2;


    DEBUGDUMPHEADER("send", "msgUserName");
    rc = asn_realloc_rbuild_string(wholeMsg, wholeMsgLen, offset, 1,
                                   (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE
                                             | ASN_OCTET_STR),
                                   (u_char *) theName, theNameLength);
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building authParams failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    DEBUGDUMPHEADER("send", "msgAuthoritativeEngineTime");
    rc = asn_realloc_rbuild_int(wholeMsg, wholeMsgLen, offset, 1,
                                (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE |
                                          ASN_INTEGER), &time_long,
                                sizeof(long));
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm",
                    "building msgAuthoritativeEngineTime failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    DEBUGDUMPHEADER("send", "msgAuthoritativeEngineBoots");
    rc = asn_realloc_rbuild_int(wholeMsg, wholeMsgLen, offset, 1,
                                (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE |
                                          ASN_INTEGER), &boots_long,
                                sizeof(long));
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm",
                    "building msgAuthoritativeEngineBoots failed.\n"));
        return SNMPERR_TOO_LONG;
    }

    DEBUGDUMPHEADER("send", "msgAuthoritativeEngineID");
    rc = asn_realloc_rbuild_string(wholeMsg, wholeMsgLen, offset, 1,
                                   (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE
                                             | ASN_OCTET_STR), theEngineID,
                                   theEngineIDLength);
    DEBUGINDENTLESS();
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building msgAuthoritativeEngineID failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    rc = asn_realloc_rbuild_sequence(wholeMsg, wholeMsgLen, offset, 1,
                                     (u_char) (ASN_SEQUENCE |
                                               ASN_CONSTRUCTOR),
                                     *offset - sp_offset);
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building usm security parameters failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    rc = asn_realloc_rbuild_header(wholeMsg, wholeMsgLen, offset, 1,
                                   (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE
                                             | ASN_OCTET_STR),
                                   *offset - sp_offset);

    if (rc == 0) {
        DEBUGMSGTL(("usm", "building msgSecurityParameters failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    while ((*wholeMsgLen - *offset) < globalDataLen) {
        if (!asn_realloc(wholeMsg, wholeMsgLen)) {
            DEBUGMSGTL(("usm", "building global data failed.\n"));
            return SNMPERR_TOO_LONG;
        }
    }

    *offset += globalDataLen;
    memcpy(*wholeMsg + *wholeMsgLen - *offset, globalData, globalDataLen);


    rc = asn_realloc_rbuild_sequence(wholeMsg, wholeMsgLen, offset, 1,
                                     (u_char) (ASN_SEQUENCE |
                                               ASN_CONSTRUCTOR), *offset);
    if (rc == 0) {
        DEBUGMSGTL(("usm", "building master packet sequence failed.\n"));
        return SNMPERR_TOO_LONG;
    }


    if (theSecLevel == SNMP_SEC_LEVEL_AUTHNOPRIV ||
        theSecLevel == SNMP_SEC_LEVEL_AUTHPRIV) {
        size_t          temp_sig_len = msgAuthParmLen;
        u_char         *temp_sig = (u_char *) malloc(temp_sig_len);
        u_char         *proto_msg = *wholeMsg + *wholeMsgLen - *offset;
        size_t          proto_msg_len = *offset;


        if (temp_sig == NULL) {
            DEBUGMSGTL(("usm", "Out of memory.\n"));
            return SNMPERR_USM_GENERICERROR;
        }

        if (sc_generate_keyed_hash(theAuthProtocol, theAuthProtocolLength,
                                   theAuthKey, theAuthKeyLength,
                                   proto_msg, proto_msg_len,
                                   temp_sig, &temp_sig_len)
            != SNMP_ERR_NOERROR) {
            SNMP_FREE(temp_sig);
            DEBUGMSGTL(("usm", "Signing failed.\n"));
            return SNMPERR_USM_AUTHENTICATIONFAILURE;
        }

        if (temp_sig_len != msgAuthParmLen) {
            SNMP_FREE(temp_sig);
            DEBUGMSGTL(("usm", "Signing lengths failed.\n"));
            return SNMPERR_USM_AUTHENTICATIONFAILURE;
        }

        memcpy(*wholeMsg + *wholeMsgLen - mac_offset, temp_sig,
               msgAuthParmLen);
        SNMP_FREE(temp_sig);
    }


    DEBUGMSGTL(("usm", "USM processing completed.\n"));
    return SNMPERR_SUCCESS;
}
