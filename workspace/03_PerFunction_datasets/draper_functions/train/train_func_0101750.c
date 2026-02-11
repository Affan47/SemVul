hashvalue(char seed, attrib1_t * attrib, char * fingerprint)
{
    MM_VSTRING	upper;
    attrib1_t *	a;
    PK11Context	*context;
	unsigned int fgLen;

    context = PK11_CreateDigestContext(SEC_OID_MD5);
	if (context != NULL) {
    	PK11_DigestBegin(context);
    	PK11_DigestOp(context, (unsigned char *)&seed, 1);
    	for (a = attrib->next; a; a = a->next) {
        	if (!stricmp(a->name, "authoritative"))
            	continue;


        	makeupper(&upper, a->name, a->namelen);
        	PK11_DigestOp(context, (unsigned char *)upper.body, upper.length);
        	PK11_DigestOp(context, (unsigned char *)"=", 1);
        	if (!memcmp(upper.body, "DN", 2)) {
            	makeupper(&upper, a->value, a->valuelen);
            	PK11_DigestOp(context, (unsigned char *)upper.body, upper.length);
        	} else
            	PK11_DigestOp(context, (unsigned char *)a->value, a->valuelen);
        	PK11_DigestOp(context, (unsigned char *)";", 1);
    	}
    	PK11_DigestFinal(context, (unsigned char *)fingerprint, &fgLen, 16);
    	PK11_DestroyContext(context, PR_TRUE);
	}
	else {
		memset(fingerprint, 0, 16);
	}
}
