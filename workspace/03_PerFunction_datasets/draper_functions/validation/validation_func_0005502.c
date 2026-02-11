Drop(CONDITION cond) {

	if(cond == DIMSE_NORMAL) {

		cond = ASC_releaseAssociation(assoc);
	}
	else if(cond == DIMSE_PEERREQUESTEDRELEASE) {
		cond = ASC_abortAssociation(assoc);
		if (SUCCESS(cond)) {
			return cond;
		}
	}
	else if(cond == DIMSE_PEERABORTEDASSOCIATION) {
		return cond;
	}
	else {
		cond = ASC_abortAssociation(assoc);
		if (SUCCESS(cond)) {
			return cond;
		}
	}

	Destroy();
	return cond;
}
