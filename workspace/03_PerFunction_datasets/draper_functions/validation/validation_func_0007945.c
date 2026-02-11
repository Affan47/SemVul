call( const unsigned long objid, const QString & func, const QStringList & fargs, KParts::LiveConnectExtension::Type & type, unsigned long & retobjid, QString & value )
{
    if (!m_viewer->appletAlive ())
        return false;
    KJavaApplet* const applet = m_viewer->view ()->appletWidget ()->applet ();
    QStringList args, ret_args;
    args.append (QString::number (applet->appletId ()));
    args.append (QString::number ((int) objid));
    args.append (func);
    {
        QStringList::const_iterator it = fargs.begin();
        const QStringList::const_iterator itEnd = fargs.end();
	for ( ; it != itEnd; ++it)
            args.append(*it);
    }

    ++m_jssessions;
    const bool ret = applet->getContext()->callMember (args, ret_args);
    --m_jssessions;
    if (!ret || ret_args.count () != 3) return false;
    bool ok;
    const int itype = ret_args[0].toInt (&ok);
    if (!ok || itype < 0) return false;
    type = (KParts::LiveConnectExtension::Type) itype;
    retobjid = ret_args[1].toInt (&ok);
    if (!ok) return false;
    value = ret_args[2];
    return true;
}
