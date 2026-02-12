unsigned CjfifDecode::ReadBe4(unsigned nPos)
{

	return (Buf(nPos)<<24) + (Buf(nPos+1)<<16) + (Buf(nPos+2)<<8) + Buf(nPos+3);
}
