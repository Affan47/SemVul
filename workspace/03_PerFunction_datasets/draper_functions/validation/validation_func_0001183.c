PrintDatabaseStats()
{
	printf("BaseArray size=%lu itemsize=%lu items=%lu\n", m_pBaseArray->Size(), (unsigned long) sizeof(struct filebaseobject), m_pBaseArray->Size()/sizeof(struct filebaseobject) );
	printf("FileBaseArray size=%lu\n", m_pFileBaseArray->Size());
	printf("PathBaseArray size=%lu\n", m_pPathBaseArray->Size());

	printf("CaseFoldedBase size=%lu itemsize=%lu items=%lu\n", m_pCaseFoldedBase->Size(), (unsigned long) sizeof(unsigned long), m_pCaseFoldedBase->Size()/sizeof(unsigned long) );
	printf("CaseFoldedData size=%lu\n", m_pCaseFoldedData->Size());

	printf("HashBaseArray size=%lu itemsize=%lu items=%lu\n", m_pHashBaseArray->Size(), (unsigned long) sizeof(struct hashbaseobject), m_pHashBaseArray->Size()/sizeof(struct hashbaseobject));
	printf("HashFileBaseArray size=%lu\n", m_pHashFileBaseArray->Size());
	printf("HashPathBaseArray size=%lu\n", m_pHashPathBaseArray->Size());
	printf("HashIndex size=%lu itemsize=%lu items=%lu\n", m_pHashIndex->Size(), (unsigned long) dcpp::TigerTree::BYTES, m_pHashIndex->Size()/dcpp::TigerTree::BYTES);

	printf("HashLeaves size=%llu (on disk)\n", CDir().getFileSize(CConfig::Instance()->GetConfigPath()+"hashleaves.bin",false));
}
