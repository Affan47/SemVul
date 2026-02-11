SendMuleInfoPacket(bool bAnswer, bool OSInfo) {

	if (m_socket == NULL){
		wxFAIL;
		return;
	}


	bool wastePackets = IsFastweb();


	CPacket* packet = NULL;
	CMemFile data;

	data.WriteUInt8(CURRENT_VERSION_SHORT);

	if (OSInfo) {


		data.WriteUInt8( 0xFF);

		data.WriteUInt32(1);

		CTagString tag1(ET_OS_INFO,theApp->GetOSType());
		tag1.WriteTagToFile(&data);

		m_OSInfo_sent = true;

	} else {


		data.WriteUInt8(EMULE_PROTOCOL);


#if 0
		data.WriteUInt32(9);
#else


		data.WriteUInt32(9 + ( wastePackets ?  1  : 0 ) );

#endif


		CTagInt32 tag1(ET_COMPRESSION,1);
		tag1.WriteTagToFile(&data);
		CTagInt32 tag2(ET_UDPVER,4);
		tag2.WriteTagToFile(&data);
		CTagInt32 tag3(ET_UDPPORT, thePrefs::GetEffectiveUDPPort());
		tag3.WriteTagToFile(&data);
		CTagInt32 tag4(ET_SOURCEEXCHANGE,3);
		tag4.WriteTagToFile(&data);
		CTagInt32 tag5(ET_COMMENTS,1);
		tag5.WriteTagToFile(&data);
		CTagInt32 tag6(ET_EXTENDEDREQUEST,2);
		tag6.WriteTagToFile(&data);

		uint32 dwTagValue = (theApp->CryptoAvailable() ? 3 : 0);


		CTagInt32 tag7(ET_FEATURES, dwTagValue);
		tag7.WriteTagToFile(&data);

		CTagInt32 tag8(ET_COMPATIBLECLIENT,SO_AMULE);
		tag8.WriteTagToFile(&data);


		wxString mod_name(MOD_VERSION_LONG);
		CTagString tag9(ET_MOD_VERSION, mod_name);
		tag9.WriteTagToFile(&data);


		if (wastePackets) {


			CTagInt32 tag10(ET_SUPERADU3, ADUNANZA_FASTWEB);
			tag10.WriteTagToFile(&data);
		}


	}

	packet = new CPacket(data, OP_EMULEPROT, (bAnswer ? OP_EMULEINFOANSWER : OP_EMULEINFO));

	if (m_socket) {
		theStats::AddUpOverheadOther(packet->GetPacketSize());
		SendPacket(packet,true,true);


#ifdef __DEBUG__

		if (!bAnswer) {
			if (!OSInfo) {
				AddDebugLogLineN( logLocalClient, wxT("Local Client: OP_EMULEINFO to ") + GetFullIP() );
			} else {
				AddDebugLogLineN( logLocalClient, wxT("Local Client: OP_EMULEINFO/OS_INFO to ") + GetFullIP() );
			}
		} else {
			AddDebugLogLineN( logLocalClient, wxT("Local Client: OP_EMULEINFOANSWER to ") + GetFullIP() );
		}


#endif

	}
}
