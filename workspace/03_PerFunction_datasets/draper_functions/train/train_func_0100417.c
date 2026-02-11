handleDirtyRings()
	{
		if(!initialized || gpg.isActive())
			return;

		if(secdirty)
			gpg.doSecretKeys();
		else if(pubdirty)
			gpg.doPublicKeys();
	}
