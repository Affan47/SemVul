cmd_strings(CLIENT_PARMS) {

    if (parsedcmdline->size() < 1) {
        snprintf(errstr, 1024, "Illegal string request");
		_MSG(errstr, MSGFLAG_ERROR);
        return -1;
    }

    int req;
    if (sscanf(((*parsedcmdline)[0]).word.c_str(), "%d", &req) != 1) {
        snprintf(errstr, 1024, "Illegal string request");
		_MSG(errstr, MSGFLAG_ERROR);
        return -1;
    }

	if (dissect_strings == 2) {
		if (req == 0)
			_MSG("String dissection cannot be disabled because it is required "
				 "by another component", MSGFLAG_INFO);
		return 1;
	}

	if (parsedcmdline->size() > 1) {
		mac_addr ma = mac_addr((*parsedcmdline)[0].word.c_str());

		if (ma.error) {
			snprintf(errstr, 1024, "String dissection, got invalid MAC address");
			_MSG(errstr, MSGFLAG_ERROR);
			return -1;
		}

		if (req) {
			string_nets.insert(ma, 1);
			_MSG("String dissection turned on for " + ma.Mac2String(), MSGFLAG_INFO);
		} else {
			string_nets.erase(ma);
			_MSG("String dissection turned off for " + ma.Mac2String(), MSGFLAG_INFO);
		}

	} else {
		if (req) {
			_MSG("String dissection from data frames enabled", MSGFLAG_INFO);
			dissect_all_strings = 1;
		} else {
			_MSG("String dissection from data frames disabled", MSGFLAG_INFO);
			dissect_all_strings = 0;
		}
	}

	dissect_strings = req;

	return 1;
}
