gth_spliced_seq_border_length(const GthSplicedSeq *spliced_seq,
                                            unsigned long position)
{
  gt_assert(gth_spliced_seq_pos_is_border(spliced_seq, position));
  return spliced_seq->positionmapping[position+1] -
         spliced_seq->positionmapping[position] - 1;
}
