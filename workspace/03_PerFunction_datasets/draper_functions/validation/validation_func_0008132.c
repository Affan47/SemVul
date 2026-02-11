encode(u_char* perm, u_int block_len, char* text)
{
	if (block_len & (block_len-1)) return "invalid permutation, number of elements must be power of 2";
	u_int numKeyBytes = block_len /8;
	u_int numBytes = strlen(text);
	u_int alignedBytes = numBytes + numBytes%numKeyBytes;
	char* out=new char[alignedBytes + 1];
	out[alignedBytes]='\0';
	std::vector< Block > bytes = bytesToBitsetArray(text, block_len);

	for (u_int i=0; i<alignedBytes; i+=numKeyBytes)
	{
		Block block(block_len);

		for (u_int bit=0; bit<block_len; ++bit)
			block[bit]=bytes[i/numKeyBytes][perm[bit]-1];


		for (u_int j=0; j<numKeyBytes; ++j)
			out[i+j]=char(block.bytes[j].to_ulong());
	}
	return out;
}
