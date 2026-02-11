init(long maxFileSize_, int maxBackupIndex_)
{
    if (maxFileSize_ < MINIMUM_ROLLING_LOG_SIZE)
    {
        tostringstream oss;
        oss << LOG4CPLUS_TEXT ("RollingFileAppender: MaxFileSize property")
            LOG4CPLUS_TEXT (" value is too small. Resetting to ")
            << MINIMUM_ROLLING_LOG_SIZE << ".";
        OFSTRINGSTREAM_GETSTR(oss, str)
        getLogLog().warn(str);
        OFSTRINGSTREAM_FREESTR(str)
        maxFileSize_ = MINIMUM_ROLLING_LOG_SIZE;
    }
    this->maxFileSize = maxFileSize_;
    if (maxBackupIndex_ < 1)
        maxBackupIndex_ = 1;
    this->maxBackupIndex = maxBackupIndex_;
}
