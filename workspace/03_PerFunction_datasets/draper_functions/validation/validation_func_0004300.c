getHeaderListLength(const uint32 contigI) const{
	STACK_TRACE_START
		if(contigI == ALL_CONTIGS)
			return spec->GetHeaderListLength();
		else{
			return spec->GetSpec(contigI)->GetHeaderListLength();
		}
	STACK_TRACE_END
}
