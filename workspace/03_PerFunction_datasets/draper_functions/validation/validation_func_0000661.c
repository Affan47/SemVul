section_already_linked (bfd *abfd, asection *sec, void *data)
{
  lang_input_statement_type *entry = (lang_input_statement_type *) data;


  if (entry->flags.just_syms)
    {
      bfd_link_just_syms (abfd, sec, &link_info);
      return;
    }

  if (!(abfd->flags & DYNAMIC))
    bfd_section_already_linked (abfd, sec, &link_info);
}
