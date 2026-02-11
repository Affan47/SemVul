GRSTasn1AddToTaglist(struct GRSTasn1TagList taglist[],
                           int maxtag, int *lasttag,
                           char *treecoords, int start, int headerlength,
                           int length, int tag)
{
   if ((strlen(treecoords) > GRST_ASN1_MAXCOORDLEN) ||
       (*lasttag + 1 > maxtag)) return;

   ++(*lasttag);

   strncpy(taglist[*lasttag].treecoords, treecoords, GRST_ASN1_MAXCOORDLEN+1);
   taglist[*lasttag].start = start;
   taglist[*lasttag].headerlength = headerlength;
   taglist[*lasttag].length = length;
   taglist[*lasttag].tag = tag;
}
