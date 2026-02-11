strip_accessgroups(void)
{
    int i, j;


    if(access_realms != NULL) {
	for (j = 0; access_realms[j] != NULL; j++) {
	    access_realms[j]->used = 0;
	}
    } else {
	syslog(L_TRACE, "No access realms to check!");
    }


    if(auth_realms != NULL) {

	for (i = 0; auth_realms[i] != NULL; i++) {

	    for (j = 0; access_realms[j] != NULL; j++) {

		if (! access_realms[j]->used) {


		    if (!access_realms[j]->key && !auth_realms[i]->key) {

			access_realms[j]->used = 1;
		    } else {


			if (access_realms[j]->key && auth_realms[i]->key &&
			    strcmp(access_realms[j]->key, auth_realms[i]->key) == 0) {

			    access_realms[j]->used = 1;
			}
		    }
		}
	    }
	}
    } else {
	syslog(L_TRACE, "No auth realms to check!");
    }


    i = j = 0;

    while (access_realms[i] != NULL) {
	if (access_realms[i]->used)
	    access_realms[j++] = access_realms[i];
	else
	    syslog(L_TRACE, "%s removing irrelevant access group %s",
		   Client.host, access_realms[i]->name);
	i++;
    }
    access_realms[j] = 0;
}
