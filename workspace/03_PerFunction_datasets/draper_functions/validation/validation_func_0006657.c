SECKEY_ImportDERPublicKey(const SECItem *derKey, CK_KEY_TYPE type)
{
    SECKEYPublicKey *pubk = NULL;
    SECStatus rv = SECFailure;
    SECItem newDerKey;
    PLArenaPool *arena = NULL;

    if (!derKey) {
        return NULL;
    }

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
        goto finish;
    }

    pubk = PORT_ArenaZNew(arena, SECKEYPublicKey);
    if (pubk == NULL) {
        goto finish;
    }
    pubk->arena = arena;

    rv = SECITEM_CopyItem(pubk->arena, &newDerKey, derKey);
    if (SECSuccess != rv) {
        goto finish;
    }

    pubk->pkcs11Slot = NULL;
    pubk->pkcs11ID = CK_INVALID_HANDLE;

    switch( type ) {
      case CKK_RSA:
	prepare_rsa_pub_key_for_asn1(pubk);
        rv = SEC_QuickDERDecodeItem(pubk->arena, pubk, SECKEY_RSAPublicKeyTemplate, &newDerKey);
        pubk->keyType = rsaKey;
        break;
      case CKK_DSA:
	prepare_dsa_pub_key_for_asn1(pubk);
        rv = SEC_QuickDERDecodeItem(pubk->arena, pubk, SECKEY_DSAPublicKeyTemplate, &newDerKey);
        pubk->keyType = dsaKey;
        break;
      case CKK_DH:
	prepare_dh_pub_key_for_asn1(pubk);
        rv = SEC_QuickDERDecodeItem(pubk->arena, pubk, SECKEY_DHPublicKeyTemplate, &newDerKey);
        pubk->keyType = dhKey;
        break;
      default:
        rv = SECFailure;
        break;
    }

finish:
    if (rv != SECSuccess) {
        if (arena != NULL) {
            PORT_FreeArena(arena, PR_TRUE);
        }
        pubk = NULL;
    }
    return pubk;
}
