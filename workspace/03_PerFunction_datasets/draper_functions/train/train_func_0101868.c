main (int argc, char *argv [])
{
  const char *file_name = NULL;
  PdfInspector *inspector;

  gtk_init (&argc, &argv);

  globalParams = new GlobalParams();
  globalParams->setProfileCommands (true);
  globalParams->setPrintCommands (true);

  if (argc == 2)
    file_name = argv[1];
  else if (argc > 2)
    {
      fprintf (stderr, "usage: %s [PDF-FILE]\n", argv[0]);
      return -1;
    }

  inspector = new PdfInspector ();

  if (file_name)
    inspector->set_file_name (file_name);

  inspector->run ();

  delete inspector;
  delete globalParams;

  return 0;
}
