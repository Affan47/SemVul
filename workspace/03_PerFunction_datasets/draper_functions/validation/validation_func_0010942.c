parse_content_type(Mime *mime, Mime_part *part, char *token,
				   Mime_parameter *param_list)
{

  if (do_content_type(part->type, token, param_list) == -1)
	return(-1);

  return(0);
}
