listusers_cb(const char *authid, const char *realm,
		  const char *mechanism, const char *secret,
		  unsigned seclen)
{
    char newPropBuffer[8192];

    if (!authid || !mechanism || !realm) {
	fprintf(stderr,"userlist callback has bad param");
	return;
    }


    if (strlen(authid)==0) return;

    printf("Converting: %s@%s (%s)...",authid,realm,mechanism);


    if(!strcmp(mechanism,"PLAIN-APOP")) {
	sprintf(newPropBuffer, "userPassword");

	secret = secret + 17;
	seclen -= 17;
    } else {
	sprintf(newPropBuffer, "cmusaslsecret%s", mechanism);
    }

    _sasldb_putdata(sasl_global_utils, globalconn,
		    authid, realm, newPropBuffer,
		    secret, seclen);

    printf("ok\n");
}
