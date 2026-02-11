kisspec_register(GlobalRegistry *in_globalreg) {
	globalreg = in_globalreg;

	if (globalreg->pcapdump == NULL || globalreg->packetchain == NULL ||
		globalreg->kismet_config == NULL || globalreg->kisnetserver == NULL)
		return 0;

	stc = new SpectoolsClient(globalreg);
	pcm_specdata = stc->FetchPacketCompId();
	globalreg->pcapdump->RegisterPPICallback(kisspec_dump, NULL);

	return 1;
}
