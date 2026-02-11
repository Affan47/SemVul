report_allocate_common(const Symbol* sym, uint64_t symsize)
{
  if (!this->printed_common_header_)
    {
      fprintf(this->map_file_, _("\nAllocating common symbols\n"));
      fprintf(this->map_file_,
	      _("Common symbol       size              file\n\n"));
      this->printed_common_header_ = true;
    }

  std::string demangled_name = sym->demangled_name();
  fprintf(this->map_file_, "%s", demangled_name.c_str());

  this->advance_to_column(demangled_name.length(), 20);

  char buf[50];
  snprintf(buf, sizeof buf, "0x%llx", static_cast<unsigned long long>(symsize));
  fprintf(this->map_file_, "%s", buf);

  size_t len = strlen(buf);
  while (len < 18)
    {
      putc(' ', this->map_file_);
      ++len;
    }

  fprintf(this->map_file_, "%s\n", sym->object()->name().c_str());
}
