Process2PublishNotesRequest(const uint8_t *packetData, uint32_t lenPacket, uint32_t ip, uint16_t port, const CKadUDPKey& senderKey)
{

	if (CUDPFirewallTester::IsFirewalledUDP(true)) {

		return;
	}

	CMemFile bio(packetData, lenPacket);
	CUInt128 target = bio.ReadUInt128();

	CUInt128 distance(CKademlia::GetPrefs()->GetKadID());
	distance.XOR(target);

	if (distance.Get32BitChunk(0) > SEARCHTOLERANCE && !::IsLanIP(wxUINT32_SWAP_ALWAYS(ip))) {
		return;
	}

	CUInt128 source = bio.ReadUInt128();

	Kademlia::CEntry* entry = new Kademlia::CEntry();
	try {
		entry->m_uIP = ip;
		entry->m_uUDPport = port;
		entry->m_uKeyID.SetValue(target);
		entry->m_uSourceID.SetValue(source);
		entry->m_bSource = false;
		uint32_t tags = bio.ReadUInt8();
		while (tags > 0) {
			CTag* tag = bio.ReadTag();
			if(tag) {
				if (!tag->GetName().Cmp(TAG_FILENAME)) {
					if (entry->GetCommonFileName().IsEmpty()) {
						entry->SetFileName(tag->GetStr());
					}
					delete tag;
				} else if (!tag->GetName().Cmp(TAG_FILESIZE)) {
					if (entry->m_uSize == 0) {
						entry->m_uSize = tag->GetInt();
					}
					delete tag;
				} else {

					entry->AddTag(tag);
				}
			}
			tags--;
		}
	} catch(...) {

		delete entry;
		entry = NULL;
		throw;
	}

	uint8_t load = 0;
	if (CKademlia::GetIndexed()->AddNotes(target, source, entry, load)) {
		CMemFile packetdata(17);
		packetdata.WriteUInt128(target);
		packetdata.WriteUInt8(load);
		DebugSend(Kad2PublishRes, ip, port);
		SendPacket(packetdata, KADEMLIA2_PUBLISH_RES, ip, port, senderKey, NULL);
	} else {
		delete entry;
	}
}
