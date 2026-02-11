handleLoggingElement(const XMLAttributes& attr)
{
    d_logFileName = attr.getValueAsString(FilenameAttribute, "");

    const String logLevel(attr.getValueAsString(LevelAttribute, ""));

    if (logLevel == "Errors")
        d_logLevel = Errors;
    else if (logLevel == "Informative")
        d_logLevel = Informative;
    else if (logLevel == "Insane")
        d_logLevel = Insane;
    else
        d_logLevel = Standard;
}
