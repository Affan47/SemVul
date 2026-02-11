lang_find_relro_sections (void)
{
  bfd_boolean has_relro_section = FALSE;


  lang_find_relro_sections_1 (expld.dataseg.relro_start_stat,
			      &has_relro_section);

  if (!has_relro_section)
    link_info.relro = FALSE;
}
