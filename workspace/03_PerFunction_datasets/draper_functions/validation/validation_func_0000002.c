copy_channels(const stp_vars_t *v)
{
  stpi_channel_group_t *cg = get_channel_group(v);
  int i, j, k;
  const unsigned short *input;
  unsigned short *output;
  if (!cg)
    return;
  input = cg->input_data;
  output = cg->output_data;
  for (i = 0; i < cg->width; i++)
    {
      for (j = 0; j < cg->channel_count; j++)
	{
	  stpi_channel_t *ch = &(cg->c[j]);
	  for (k = 0; k < ch->subchannel_count; k++)
	    {
	      if (cg->gloss_channel != j)
		{
		  *output = *input++;
		}
	      output++;
	    }
	}
    }
}
