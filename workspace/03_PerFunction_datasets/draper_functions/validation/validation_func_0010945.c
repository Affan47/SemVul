update(const UT_UTF8String &sMessage)
{
    m_sBuf = sMessage;

    if (getListener())
	getListener()->notify();
}
