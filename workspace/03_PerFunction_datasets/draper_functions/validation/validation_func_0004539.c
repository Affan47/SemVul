ar_addlib_doer (bfd *abfd, bfd *prev)
{

  if (prev != NULL)
    prev->archive_next = abfd->archive_next;

  abfd->archive_next = obfd->archive_head;
  obfd->archive_head = abfd;
}
