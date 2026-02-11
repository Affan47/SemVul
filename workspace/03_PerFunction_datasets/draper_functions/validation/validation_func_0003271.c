format_check (void *msgid_descr, void *msgstr_descr, bool equality,
              formatstring_error_logger_t error_logger,
              const char *pretty_msgid, const char *pretty_msgstr)
{
  struct spec *spec1 = (struct spec *) msgid_descr;
  struct spec *spec2 = (struct spec *) msgstr_descr;
  bool err = false;


  if (equality
      ? spec1->numbered_arg_count != spec2->numbered_arg_count
      : spec1->numbered_arg_count < spec2->numbered_arg_count)
    {
      if (error_logger)
        error_logger (_("number of format specifications in '%s' and '%s' does not match"),
                      pretty_msgid, pretty_msgstr);
      err = true;
    }

  return err;
}
