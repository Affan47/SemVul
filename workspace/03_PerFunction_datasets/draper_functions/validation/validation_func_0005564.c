add_huff_table (j_compress_ptr cinfo,
		JHUFF_TBL **htblptr, const UINT8 *bits, const UINT8 *val)

{
  int nsymbols, len;

  if (*htblptr == NULL)
    *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);


  MEMCOPY((*htblptr)->bits, bits, SIZEOF((*htblptr)->bits));


  nsymbols = 0;
  for (len = 1; len <= 16; len++)
    nsymbols += bits[len];
  if (nsymbols < 1 || nsymbols > 256)
    ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);

  MEMCOPY((*htblptr)->huffval, val, nsymbols * SIZEOF(UINT8));


  (*htblptr)->sent_table = FALSE;
}
