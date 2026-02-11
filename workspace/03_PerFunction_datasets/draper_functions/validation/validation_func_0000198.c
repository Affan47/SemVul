port() const
{
    if (hasAttribute(QLatin1String("port")))
    {
        bool ok;
        int c = attribute(QLatin1String("port")).toInt(&ok);
        return ok ? c : -1;
    }

    return -1;
}
