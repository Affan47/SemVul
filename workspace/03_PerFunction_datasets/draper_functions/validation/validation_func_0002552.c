decompress(
	void						*inData,
	size_t						inDataSize,
	void						*outData,
	size_t						outDataBufferSize,
	size_t						&outDataActualSize)
{
	int ret=0;
	MRPT_START

	unsigned long	actualOutSize = (unsigned long)outDataBufferSize;

	ret = ::uncompress(
		(unsigned char*)outData,
		&actualOutSize,
		(unsigned char*)inData,
		(unsigned long)inDataSize
		);

	ASSERT_(ret==Z_OK);

	outDataActualSize = actualOutSize;

	MRPT_END_WITH_CLEAN_UP( \
		printf("[zlib] Error code=%i\n",ret);\
		);
}
