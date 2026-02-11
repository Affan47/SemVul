GetContigSeqLength( const uint32 i ) const
{
	if( i < m_contigList.size() ){
		return m_contigList[i]->GetSeqLength();
	}else if( i == ALL_CONTIGS){
		gnSeqI seqlen = 0;
		for(uint32 j=0; j < m_contigList.size(); j++)
			seqlen += m_contigList[j]->GetSeqLength();
		return seqlen;
	}
	return GNSEQI_ERROR;
}
