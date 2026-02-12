void CSoundFile::InstrumentChange(ModChannel *pChn, uint32 instr, bool bPorta, bool bUpdVol, bool bResetEnv) const
{
	const ModInstrument *pIns = instr <= GetNumInstruments() ? Instruments[instr] : nullptr;
	const ModSample *pSmp = &Samples[instr];
	ModCommand::NOTE note = pChn->nNewNote;

	if(note == NOTE_NONE && m_playBehaviour[kITInstrWithoutNote]) return;

	if(pIns != nullptr && ModCommand::IsNote(note))
	{


		if(pIns->Keyboard[note - NOTE_MIN] == 0 && m_playBehaviour[kITEmptyNoteMapSlot] && !pIns->HasValidMIDIChannel())
		{
			pChn->pModInstrument = pIns;
			return;
		}

		if(pIns->NoteMap[note - NOTE_MIN] > NOTE_MAX) return;
		uint32 n = pIns->Keyboard[note - NOTE_MIN];
		pSmp = ((n) && (n < MAX_SAMPLES)) ? &Samples[n] : nullptr;
	} else if(GetNumInstruments())
	{

		if (note >= NOTE_MIN_SPECIAL) return;
		if(m_playBehaviour[kITEmptyNoteMapSlot] && (pIns == nullptr || !pIns->HasValidMIDIChannel()))
		{


			pChn->pModInstrument = nullptr;
			pChn->nNewIns = 0;
			return;
		}
		pSmp = nullptr;
	}

	bool returnAfterVolumeAdjust = false;


	bool instrumentChanged = (pIns != pChn->pModInstrument);
	const bool sampleChanged = (pChn->pModSample != nullptr) && (pSmp != pChn->pModSample);

	const bool newTuning = (GetType() == MOD_TYPE_MPT && pIns && pIns->pTuning);


	if(bPorta && newTuning && pIns == pChn->pModInstrument && sampleChanged)
		return;

	if(sampleChanged && bPorta)
	{


		if(m_playBehaviour[kITPortamentoInstrument] && m_SongFlags[SONG_ITCOMPATGXX] && !pChn->increment.IsZero())
		{
			pSmp = pChn->pModSample;
		}


		if((!instrumentChanged && (GetType() & (MOD_TYPE_XM | MOD_TYPE_MT2)) && pIns)
			|| (GetType() == MOD_TYPE_PLM)
			|| (GetType() == MOD_TYPE_MOD && pChn->IsSamplePlaying())
			|| m_playBehaviour[kST3PortaSampleChange])
		{


			returnAfterVolumeAdjust = true;
		}
	}


	if(m_nInstruments && !instrumentChanged && sampleChanged && pChn->pCurrentSample != nullptr && m_playBehaviour[kITMultiSampleInstrumentNumber] && !pChn->rowCommand.IsNote())
	{
		returnAfterVolumeAdjust = true;
	}


	if(!pChn->IsSamplePlaying() && (GetType() & (MOD_TYPE_IT | MOD_TYPE_MPT)) && (!pIns || !pIns->HasValidMIDIChannel()))
	{
		instrumentChanged = true;
	}


	if(instrumentChanged && bPorta && m_playBehaviour[kFT2PortaIgnoreInstr] && (pChn->pModInstrument != nullptr || pChn->pModSample != nullptr))
	{
		pIns = pChn->pModInstrument;
		pSmp = pChn->pModSample;
		instrumentChanged = false;
	} else
	{
		pChn->pModInstrument = pIns;
	}


	if (bUpdVol && (!(GetType() & (MOD_TYPE_MOD | MOD_TYPE_S3M)) || ((pSmp != nullptr && pSmp->HasSampleData()) || pChn->HasMIDIOutput())))
	{
		if(pSmp)
		{
			if(!pSmp->uFlags[SMP_NODEFAULTVOLUME])
				pChn->nVolume = pSmp->nVolume;
		} else if(pIns && pIns->nMixPlug)
		{
			pChn->nVolume = pChn->GetVSTVolume();
		} else
		{
			pChn->nVolume = 0;
		}
	}

	if(returnAfterVolumeAdjust && sampleChanged && m_playBehaviour[kMODSampleSwap] && pSmp != nullptr)
	{


		pChn->nFineTune = pSmp->nFineTune;
	}

	if(returnAfterVolumeAdjust) return;


	pChn->nNewIns = 0;


	if (pIns && ((!m_playBehaviour[kITNNAReset] && pSmp) || pIns->nMixPlug))
		pChn->nNNA = pIns->nNNA;


	pChn->UpdateInstrumentVolume(pSmp, pIns);


	if((bUpdVol || !(GetType() & (MOD_TYPE_XM | MOD_TYPE_MT2))) && !m_playBehaviour[kITPanningReset])
	{
		ApplyInstrumentPanning(pChn, pIns, pSmp);
	}


	if(bResetEnv)
	{


		bool reset, resetAlways;


		if(m_playBehaviour[kITEnvelopeReset])
		{
			const bool insNumber = (instr != 0);
			reset = (!pChn->nLength
				|| (insNumber && bPorta && m_SongFlags[SONG_ITCOMPATGXX])
				|| (insNumber && !bPorta && pChn->dwFlags[CHN_NOTEFADE | CHN_KEYOFF] && m_SongFlags[SONG_ITOLDEFFECTS]));


			resetAlways = (!pChn->nFadeOutVol || instrumentChanged || pChn->dwFlags[CHN_KEYOFF]);
		} else
		{
			reset = (!bPorta || !(GetType() & (MOD_TYPE_IT | MOD_TYPE_MPT | MOD_TYPE_DBM)) || m_SongFlags[SONG_ITCOMPATGXX]
				|| !pChn->nLength || (pChn->dwFlags[CHN_NOTEFADE] && !pChn->nFadeOutVol));
			resetAlways = !(GetType() & (MOD_TYPE_IT | MOD_TYPE_MPT | MOD_TYPE_DBM)) || instrumentChanged || pIns == nullptr || pChn->dwFlags[CHN_KEYOFF | CHN_NOTEFADE];
		}

		if(reset)
		{
			pChn->dwFlags.set(CHN_FASTVOLRAMP);
			if(pIns != nullptr)
			{
				if(resetAlways)
				{
					pChn->ResetEnvelopes();
				} else
				{
					if(!pIns->VolEnv.dwFlags[ENV_CARRY]) pChn->VolEnv.Reset();
					if(!pIns->PanEnv.dwFlags[ENV_CARRY]) pChn->PanEnv.Reset();
					if(!pIns->PitchEnv.dwFlags[ENV_CARRY]) pChn->PitchEnv.Reset();
				}
			}


			if(!m_playBehaviour[kITVibratoTremoloPanbrello])
			{
				pChn->nAutoVibDepth = 0;
				pChn->nAutoVibPos = 0;
			}
		} else if(pIns != nullptr && !pIns->VolEnv.dwFlags[ENV_ENABLED])
		{
			if(m_playBehaviour[kITPortamentoInstrument])
			{
				pChn->VolEnv.Reset();
			} else
			{
				pChn->ResetEnvelopes();
			}
		}
	}

	if(pSmp == nullptr && (pIns == nullptr || !pIns->HasValidMIDIChannel()))
	{
		pChn->pModSample = nullptr;
		pChn->nInsVol = 0;
		return;
	}


	if(bPorta && pSmp == pChn->pModSample && pSmp != nullptr)
	{

		if(GetType() & (MOD_TYPE_S3M|MOD_TYPE_IT|MOD_TYPE_MPT) && pChn->nLength != 0) return;
		pChn->dwFlags.reset(CHN_KEYOFF | CHN_NOTEFADE);
		pChn->dwFlags = (pChn->dwFlags & (CHN_CHANNELFLAGS | CHN_PINGPONGFLAG));
	} else
	{
		pChn->dwFlags.reset(CHN_KEYOFF | CHN_NOTEFADE);


		if((m_playBehaviour[kITPingPongNoReset] || !(GetType() & (MOD_TYPE_IT | MOD_TYPE_MPT))) && pSmp == pChn->pModSample && !instrumentChanged)
			pChn->dwFlags = (pChn->dwFlags & (CHN_CHANNELFLAGS | CHN_PINGPONGFLAG));
		else
			pChn->dwFlags = (pChn->dwFlags & CHN_CHANNELFLAGS);

		if(pIns)
		{

			pChn->VolEnv.flags = pIns->VolEnv.dwFlags;
			pChn->PanEnv.flags = pIns->PanEnv.dwFlags;
			pChn->PitchEnv.flags = pIns->PitchEnv.dwFlags;


			if((pIns->PitchEnv.dwFlags & (ENV_ENABLED | ENV_FILTER)) == (ENV_ENABLED | ENV_FILTER) && !m_playBehaviour[kITFilterBehaviour])
			{
				if(!pChn->nCutOff) pChn->nCutOff = 0x7F;
			}

			if(pIns->IsCutoffEnabled()) pChn->nCutOff = pIns->GetCutoff();
			if(pIns->IsResonanceEnabled()) pChn->nResonance = pIns->GetResonance();
		}
	}

	if(pSmp == nullptr)
	{
		pChn->pModSample = nullptr;
		pChn->nLength = 0;
		return;
	}

	if(bPorta && pChn->nLength == 0 && (m_playBehaviour[kFT2PortaNoNote] || m_playBehaviour[kITPortaNoNote]))
	{


		pChn->increment.Set(0);
	}

	pChn->pModSample = pSmp;
	pChn->nLength = pSmp->nLength;
	pChn->nLoopStart = pSmp->nLoopStart;
	pChn->nLoopEnd = pSmp->nLoopEnd;

	if(m_playBehaviour[kMODOneShotLoops] && pChn->nLoopStart == 0) pChn->nLoopEnd = pSmp->nLength;
	pChn->dwFlags |= (pSmp->uFlags & (CHN_SAMPLEFLAGS | CHN_SURROUND));


	if(m_playBehaviour[kITVibratoTremoloPanbrello])
	{
		pChn->nAutoVibDepth = 0;
		pChn->nAutoVibPos = 0;
	}

	if(newTuning)
	{
		pChn->nC5Speed = pSmp->nC5Speed;
		pChn->m_CalculateFreq = true;
		pChn->nFineTune = 0;
	} else if(!bPorta || sampleChanged || !(GetType() & (MOD_TYPE_MOD | MOD_TYPE_XM)))
	{


		pChn->nC5Speed = pSmp->nC5Speed;
		pChn->nFineTune = pSmp->nFineTune;
	}


	pChn->nTranspose = pSmp->RelativeTone;


	if(!m_playBehaviour[kFT2PortaTargetNoReset] && GetType() != MOD_TYPE_MOD)
	{
		pChn->nPortamentoDest = 0;
	}
	pChn->m_PortamentoFineSteps = 0;

	if(pChn->dwFlags[CHN_SUSTAINLOOP])
	{
		pChn->nLoopStart = pSmp->nSustainStart;
		pChn->nLoopEnd = pSmp->nSustainEnd;
		if(pChn->dwFlags[CHN_PINGPONGSUSTAIN]) pChn->dwFlags.set(CHN_PINGPONGLOOP);
		pChn->dwFlags.set(CHN_LOOP);
	}
	if(pChn->dwFlags[CHN_LOOP] && pChn->nLoopEnd < pChn->nLength) pChn->nLength = pChn->nLoopEnd;


	if(pChn->position.GetUInt() >= pChn->nLength)
	{
		if((GetType() & (MOD_TYPE_IT | MOD_TYPE_MPT)))
		{
			pChn->position.Set(0);
		}
	}
}
