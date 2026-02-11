capi20_put_message( unsigned ApplID, unsigned char *Msg ) {
	if (capi20_isinstalled() != CapiNoError) {
		return CapiRegNotInstalled;
	}

	if (!capi_validapplid(ApplID)) {
		return CapiIllAppNr;
	}

	return psModule->psOperations->PutMessage(capi_applid2fd(ApplID), ApplID, Msg);
}
