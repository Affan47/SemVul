graph_all(void)
{
  int i;


  fprintf(out_file, "%s: %s\n",
	  current_map->block_family, current_map->description);
  fprintf(out_file, "%d distinct blocks in %d sequences\n",
	  current_map->tot_num_blocks, current_map->num_seqs);


  maxlength = current_map->max_seq_len;


  for (i = 0; i < current_map->num_seqs; i++)
  {
    make_graph(current_map->seq_map + i);
  }


  if (o_scale != SCALE_FLUSH)
  {
    fprintf(out_file, "%20s---- %d amino acids\n\n", "", square_size(4));
  }
}
