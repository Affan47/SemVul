CjfifDecode::~CjfifDecode()
{

	if (m_pPsDec) {
		delete m_pPsDec;
		m_pPsDec = NULL;
	}

#ifdef SUPPORT_DICOM

	if (m_pDecDicom) {
		delete m_pDecDicom;
		m_pDecDicom = NULL;
	}
#endif

}
