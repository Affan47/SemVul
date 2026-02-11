EmptySeq(long I, long length)

{
	char	*seq;
	e_type	E;

	NEW(seq,length+1, char);
	NEW(E,1,sequence_type);
	E->info=NULL;  E->n = (unsigned short) length;
        E->I = (unsigned short) I;
        E->S = seq;  E->X = seq; E->xnu = FALSE;
        return E;
}
