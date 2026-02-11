HasHoloMero(IndexPtr index, int ptrtyp)
{
    int i, j;
    SynsetPtr synset, psynset;
    int found=0;
    int ptrbase;

    ptrbase = (ptrtyp == HMERONYM) ? HASMEMBERPTR : ISMEMBERPTR;

    for(i = 0; i < index->off_cnt; i++) {
	synset = read_synset(NOUN, index->offset[i], "");
	for (j = 0; j < synset->ptrcount; j++) {
	    if (synset->ptrtyp[j] == HYPERPTR) {
		psynset = read_synset(NOUN, synset->ptroff[j], "");
		found += HasPtr(psynset, ptrbase);
		found += HasPtr(psynset, ptrbase + 1);
		found += HasPtr(psynset, ptrbase + 2);

		free_synset(psynset);
	    }
	}
	free_synset(synset);
    }
    return(found);
}
