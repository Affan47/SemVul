add_line_info (table, address, filename, line, column, end_sequence)
     struct line_info_table* table;
     bfd_vma address;
     char* filename;
     unsigned int line;
     unsigned int column;
     int end_sequence;
{
  bfd_size_type amt = sizeof (struct line_info);
  struct line_info* info = (struct line_info*) bfd_alloc (table->abfd, amt);


  while (1)
    if (!table->last_line
	|| address >= table->last_line->address)
      {

	info->prev_line = table->last_line;
	table->last_line = info;


	if (!table->lcl_head)
	  table->lcl_head = info;
	break;
      }
    else if (!table->lcl_head->prev_line
	     && table->lcl_head->address > address)
      {


	info->prev_line = NULL;
	table->lcl_head->prev_line = info;
	break;
      }
    else if (table->lcl_head->prev_line
	     && table->lcl_head->address > address
	     && address >= table->lcl_head->prev_line->address)
      {


	info->prev_line = table->lcl_head->prev_line;
	table->lcl_head->prev_line = info;
	break;
      }
    else
      {


	struct line_info* li2 = table->last_line;
	struct line_info* li1 = li2->prev_line;

	while (li1)
	  {
	    if (li2->address > address && address >= li1->address)
	      break;

	    li2 = li1;
	    li1 = li1->prev_line;
	  }
	table->lcl_head = li2;
      }


  info->address = address;
  info->line = line;
  info->column = column;
  info->end_sequence = end_sequence;

  amt = strlen (filename);
  if (amt)
    {
      info->filename = bfd_alloc (table->abfd, amt + 1);
      if (info->filename)
	strcpy (info->filename, filename);
    }
  else
    info->filename = NULL;
}
