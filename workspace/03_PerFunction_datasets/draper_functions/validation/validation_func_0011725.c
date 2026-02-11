main(void)
{
  ppdcSource	*src;
  ppdcCatalog	*catalog;


  if (access("../data", 0) || access("sample.drv", 0))
  {
    puts("You must run genstrings from the ppdc directory.");
    return (1);
  }


  ppdcSource::add_include("../data");

  src     = new ppdcSource("sample.drv");
  catalog = new ppdcCatalog(NULL);

  catalog->add_message("ISOLatin1");
  catalog->add_message("English");


  ppdcMediaSize	*size;

  for (size = (ppdcMediaSize *)src->sizes->first();
       size;
       size = (ppdcMediaSize *)src->sizes->next())
    catalog->add_message(size->text->value);


  ppdcDriver	*d;

  for (d = (ppdcDriver *)src->drivers->first();
       d;
       d = (ppdcDriver *)src->drivers->next())
    add_ui_strings(d, catalog);


  ppdcMessage *message;

  for (message = (ppdcMessage *)catalog->messages->first();
       message;
       message = (ppdcMessage *)catalog->messages->next())
    write_cstring(message->id->value);

  src->release();
  catalog->release();


  return (0);
}
