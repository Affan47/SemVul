HuffmanTree_makeFromLengths(HuffmanTree* tree, const unsigned* bitlen, size_t numcodes, unsigned maxbitlen)
{
  unsigned i;
  if(!uivector_resize(&tree->lengths, numcodes)) return 9903;
  for(i = 0; i < numcodes; i++) tree->lengths.data[i] = bitlen[i];
  tree->numcodes = (unsigned)numcodes;
  tree->maxbitlen = maxbitlen;
  return HuffmanTree_makeFromLengths2(tree);
}
