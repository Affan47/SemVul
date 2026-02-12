mp_sint32 PlayerGeneric::startPlaying(XModule* module,
									  bool repeat,
									  mp_uint32 startPosition,
									  mp_uint32 startRow,
									  mp_sint32 numChannels,
									  const mp_ubyte* customPanningTable,
									  bool idle,
									  mp_sint32 patternIndex,
									  bool playOneRowOnly)
{
	this->idle = idle;
	this->repeat = repeat;
	this->playOneRowOnly = playOneRowOnly;

	if (mixer == NULL)
	{
		mixer = new MasterMixer(frequency, bufferSize, 1, audioDriver);
		mixer->setMasterMixerNotificationListener(listener);
		mixer->setSampleShift(sampleShift);
		if (audioDriver == NULL)
			mixer->setCurrentAudioDriverByName(audioDriverName);
	}

	if (!player || player->getType() != getPreferredPlayerType(module))
	{
		if (player)
		{
			if (!mixer->isDeviceRemoved(player))
				mixer->removeDevice(player);
			delete player;
		}

		player = getPreferredPlayer(module);

		if (player)
		{

			player->resetMainVolumeOnStartPlay(resetMainVolumeOnStartPlayFlag);
			player->resetOnStop(resetOnStopFlag);
			player->setBufferSize(bufferSize);
			player->setResamplerType(resamplerType);
			player->setMasterVolume(masterVolume);
			player->setPanningSeparation(panningSeparation);
			player->setPlayMode(playMode);

			for (mp_sint32 i = PlayModeOptionFirst; i < PlayModeOptionLast; i++)
				player->enable((PlayModeOptions)i, options[i]);

			player->setDisableMixing(disableMixing);
			player->setAllowFilters(allowFilters);


			setNumMaxVirChannels(numMaxVirChannels);
		}
	}

	if (player && mixer)
	{
		if (!mixer->isDeviceRemoved(player))
			mixer->removeDevice(player);

		player->startPlaying(module, repeat, startPosition, startRow, numChannels, customPanningTable, idle, patternIndex, playOneRowOnly);

		mixer->addDevice(player);

		if (!mixer->isPlaying())
			return mixer->start();
	}


	return MP_OK;
}
