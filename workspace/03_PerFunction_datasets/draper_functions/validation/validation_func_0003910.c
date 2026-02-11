decompress(
	CStream						&inStream,
	size_t						inDataSize,
	void						*outData,
	size_t						outDataBufferSize,
	size_t						&outDataActualSize)
{
	int ret=0;
	MRPT_START

	unsigned long	actualOutSize = (unsigned long)outDataBufferSize;
	std::vector<unsigned char>		inData;

	inData.resize(inDataSize);
	inStream.ReadBuffer( &inData[0], inDataSize );

	ret = ::uncompress(
		(unsigned char*)outData,
		&actualOutSize,
		&inData[0],
		(unsigned long)inDataSize
		);

	ASSERT_(ret==Z_OK);

	outDataActualSize = actualOutSize;

	MRPT_END_WITH_CLEAN_UP( \
		printf("[zlib] Error code=%i\n",ret);\
		);
}
