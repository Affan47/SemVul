timeZone() const
{
    if (d->type == KDateTime::TimeZone)
        return d->tz;
    if (d->type == KDateTime::UTC)
        return KTimeZone::utc();
    return KTimeZone();
}
