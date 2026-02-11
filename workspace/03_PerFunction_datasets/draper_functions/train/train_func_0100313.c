main(int argc, char *argv[])
{
  int error_count = 0;
  MdfConsoleEngine engine(argc, argv, OFFIS_CONSOLE_APPLICATION);
  error_count = engine.startProvidingService();
  if (error_count == 1)
    OFLOG_ERROR(dcmodifyLogger, "There was 1 error");
  else if (error_count > 1)
    OFLOG_ERROR(dcmodifyLogger, "There were " << error_count << " errors");
  return(error_count);
}
