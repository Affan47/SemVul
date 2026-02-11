wti_mpc_hostlist(StonithPlugin * s)
{
    char **hl;
    struct pluginDevice *ad;
    int j, h, num_outlets;
    char *outlet_name;
    char objname[MAX_STRING];

    DEBUGCALL;

    ERRIFNOTCONFIGED(s, NULL);

    ad = (struct pluginDevice *) s;


    if ((hl = (char **)MALLOC((ad->num_outlets+1) * sizeof(char *))) == NULL) {
	LOG(PIL_CRIT, "%s: out of memory.", __FUNCTION__);
	return (NULL);
    }

    memset(hl, 0, (ad->num_outlets + 1) * sizeof(char *));
    num_outlets = 0;


    for (j = 0; j < ad->num_outlets; ++j) {


	switch (ad->mib_version) {
	    case 3:
                snprintf(objname,MAX_STRING,OID_GROUP_NAMES_V3,j+1);
                break;
            case 1:
            default:
                snprintf(objname,MAX_STRING,OID_GROUP_NAMES_V1,j+1);
		break;
	}
	if (Debug) {
	    LOG(PIL_DEBUG, "%s: using %s as group names oid", __FUNCTION__, objname);
	}


	if ((outlet_name = MPC_read(ad->sptr, objname, ASN_OCTET_STR)) ==
	    NULL) {
	    LOG(PIL_CRIT, "%s: cannot read name for outlet %d."
            ,   __FUNCTION__, j+1);
	    stonith_free_hostlist(hl);
	    hl = NULL;
	    return (hl);
	}


	for (h = 0; h < num_outlets; ++h) {
		if (strcasecmp(hl[h],outlet_name) == 0)
			break;
	}

	if (h >= num_outlets) {

		if (Debug) {
	            LOG(PIL_DEBUG, "%s: added %s to hostlist."
		    ,   __FUNCTION__, outlet_name);
		}

		if ((hl[num_outlets] = STRDUP(outlet_name)) == NULL) {
		    LOG(PIL_CRIT, "%s: out of memory.", __FUNCTION__);
		    stonith_free_hostlist(hl);
		    hl = NULL;
		    return (hl);
		}
		g_strdown(hl[num_outlets]);
		num_outlets++;
	}
    }


    if (Debug) {
    	LOG(PIL_DEBUG, "%s: %d unique hosts connected to %d outlets."
	,   __FUNCTION__, num_outlets, j);
    }

    return (hl);
}
