put(const unsigned long objid, const QString & name, const QString & value)
{
    if (!m_viewer->appletAlive ())
        return false;
    QStringList args;
    KJavaApplet* const applet = m_viewer->view ()->appletWidget ()->applet ();
    args.append (QString::number (applet->appletId ()));
    args.append (QString::number ((int) objid));
    args.append (name);
    args.append (value);
    ++m_jssessions;
    const bool ret = applet->getContext()->putMember (args);
    --m_jssessions;
    return ret;
}
