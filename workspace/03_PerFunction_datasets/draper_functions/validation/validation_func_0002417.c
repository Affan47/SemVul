setup()
{

  if (this->input_file_->file().filesize() == sarmag)
    return;


  std::string armap_name;
  off_t header_size = this->read_header(sarmag, false, &armap_name, NULL);
  if (header_size == -1)
    return;

  section_size_type armap_size = convert_to_section_size_type(header_size);
  off_t off = sarmag;
  if (armap_name.empty())
    {
      this->read_armap(sarmag + sizeof(Archive_header), armap_size);
      off = sarmag + sizeof(Archive_header) + armap_size;
    }
  else if (!this->input_file_->options().whole_archive())
    gold_error(_("%s: no archive symbol table (run ranlib)"),
	       this->name().c_str());


  if ((off & 1) != 0)
    ++off;
  std::string xname;
  header_size = this->read_header(off, true, &xname, NULL);
  if (header_size == -1)
    return;

  section_size_type extended_size = convert_to_section_size_type(header_size);
  if (xname == "/")
    {
      const unsigned char* p = this->get_view(off + sizeof(Archive_header),
                                              extended_size, false, true);
      const char* px = reinterpret_cast<const char*>(p);
      this->extended_names_.assign(px, extended_size);
    }
  bool preread_syms = (parameters->options().threads()
                       && parameters->options().preread_archive_symbols());
#ifndef ENABLE_THREADS
  preread_syms = false;
#else
  if (parameters->options().has_plugins())
    preread_syms = false;
#endif
  if (preread_syms)
    this->read_all_symbols();
}
