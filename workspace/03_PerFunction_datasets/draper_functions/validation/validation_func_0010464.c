translate_sequence_collection_default(struct seq_col *in_seq_col)
{
	int i;
	for(i=0; i!= in_seq_col->length; ++i)
		translate_sequence( &(in_seq_col->seqs[i]) );
}
