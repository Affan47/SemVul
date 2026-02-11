configureLoggers()
{
    if(properties.exists( LOG4CPLUS_TEXT("rootLogger") ))
    {
        Logger root = h.getRoot();
        configureLogger(root,
                        properties.getProperty(LOG4CPLUS_TEXT("rootLogger")));
    }

    Properties loggerProperties
        = properties.getPropertySubset(LOG4CPLUS_TEXT("logger."));
    std::vector<tstring> loggers = loggerProperties.propertyNames();
    for(std::vector<tstring>::iterator it=loggers.begin(); it!=loggers.end();
        ++it)
    {
        Logger log = getLogger(*it);
        configureLogger(log, loggerProperties.getProperty(*it));
    }
}
