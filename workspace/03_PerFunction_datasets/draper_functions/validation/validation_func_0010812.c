parse_lh(struct hive *hdesc, int vofs, int blen)
{
  struct lf_key *key;
  int i;

  printf("== lh at offset %0x\n",vofs);

  key = (struct lf_key *)(hdesc->buffer + vofs);
  printf("%04x   number of keys    = %d\n", D_OFFS(no_keys), key->no_keys  );

  for(i = 0; i < key->no_keys; i++) {
    printf("%04x      %3d   Offset: 0x%0x  - <hash: %08x>\n",
	   D_OFFS(lh_hash[i].ofs_nk), i,
	   key->lh_hash[i].ofs_nk + 0x1000,
           key->lh_hash[i].hash );
  }

  printf("== End of key info.\n");

}
