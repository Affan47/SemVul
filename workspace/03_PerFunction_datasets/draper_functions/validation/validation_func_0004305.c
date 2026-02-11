prev_hline(int *entry, struct hdr_line *line)
{
    if(line == NULL)
      return(NULL);

    if(line->prev == NULL){
	int orig_entry;

	orig_entry = *entry;
	while(--(*entry) >= 0){
	    if(headents[*entry].display_it){
		line = headents[*entry].hd_text;
		while(line->next != NULL)
		  line = line->next;
		return(line);
	    }
	}

	*entry = orig_entry;
	return(NULL);
    }
    else
      return(line->prev);
}
