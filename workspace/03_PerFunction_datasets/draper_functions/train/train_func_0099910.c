IsComplete(uint16 part)
{


	if (part == m_iPartCount && m_sizeLastPart == PARTSIZE) {
		return true;
	}

	if (part >= m_iPartCount) {
		wxFAIL;
		return false;
	}
	ePartComplete status = (ePartComplete) m_partsComplete[part];
	if (status == unknown) {
		uint64 partstart = part * PARTSIZE;
		uint64 partend = partstart + GetPartSize(part) - 1;
		status = IsComplete(partstart, partend) ? complete : incomplete;
		m_partsComplete[part] = status;
	}
	return status == complete;
}
