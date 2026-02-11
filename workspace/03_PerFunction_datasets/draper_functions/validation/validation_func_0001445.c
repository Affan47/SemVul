mem_list_dump()
{ struct memhead *head;
  size_t subcount;

#ifdef MEMSTRINGS
  outstring("\nEternal memory blocks:\n");
  for ( head = eternal_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p; %28s line %4d\n",
      subcount,head->size,head,head->file,head->line);
    outstring(msg);
  }

  outstring("\nPermanent memory blocks:\n");
  for ( head = perm_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p; %28s line %4d\n",
      subcount,head->size,head,head->file,head->line);
    outstring(msg);
  }

  outstring("\nTemporary memory blocks:\n");
  for ( head = temp_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p; %28s line %4d\n",
      subcount,head->size,head,head->file,head->line);
    outstring(msg);
  }

  outstring("\nGraph memory blocks:\n");
  for ( head = graph_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p; %28s line %4d\n",
      subcount,head->size,head,head->file,head->line);
    outstring(msg);
  }
#else
  outstring("\nEternal memory blocks:\n");
  for ( head = eternal_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p\n",
      subcount,head->size,head);
    outstring(msg);
  }

  outstring("\nPermanent memory blocks:\n");
  for ( head = perm_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p\n",
      subcount,head->size,head);
    outstring(msg);
  }

  outstring("\nTemporary memory blocks:\n");
  for ( head = temp_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p\n",
      subcount,head->size,head);
    outstring(msg);
  }

  outstring("\nGraph memory blocks:\n");
  for ( head = graph_block_head, subcount=0 ; head ; head = head->next )
  { subcount++;
    sprintf(msg,"%5d. %10d bytes at %p\n",
      subcount,head->size,head);
    outstring(msg);
  }
#endif
}
