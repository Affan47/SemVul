void LogHandler::setupStdoutLogger() {
  el::Logger *stdoutLogger = el::Loggers::getLogger("stdout");

  el::Configurations stdoutConf;
  stdoutConf.setToDefault();

  stdoutConf.setGlobally(el::ConfigurationType::Format, "%msg");
  stdoutConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
  stdoutConf.setGlobally(el::ConfigurationType::ToFile, "false");
  el::Loggers::reconfigureLogger(stdoutLogger, stdoutConf);
}
