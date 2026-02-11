smime_policy_algorithm (SECAlgorithmID *algid, PK11SymKey *key)
{
    SECOidTag algtag;

    algtag = SECOID_GetAlgorithmTag (algid);
    switch (algtag) {
      case SEC_OID_RC2_CBC:
	{
	    unsigned int keylen_bits;

	    keylen_bits = PK11_GetKeyStrength (key, algid);
	    switch (keylen_bits) {
	      case 40:
		return SMIME_RC2_CBC_40;
	      case 64:
		return SMIME_RC2_CBC_64;
	      case 128:
		return SMIME_RC2_CBC_128;
	      default:
		break;
	    }
	}
	break;
      case SEC_OID_DES_CBC:
	return SMIME_DES_CBC_56;
      case SEC_OID_DES_EDE3_CBC:
	return SMIME_DES_EDE3_168;
#ifdef SMIME_DOES_RC5
      case SEC_OID_RC5_CBC_PAD:
	PORT_Assert (0);
	break;
#endif
      default:
	break;
    }

    return -1;
}
