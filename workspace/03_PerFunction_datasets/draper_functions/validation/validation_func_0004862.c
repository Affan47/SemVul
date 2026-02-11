eatCookie(KHttpCookieList::iterator cookieIterator)
{
    const KHttpCookie& cookie = *cookieIterator;
    const QString domain = stripDomain(cookie);
    KHttpCookieList *cookieList = m_cookieDomains.value(domain);

    if (cookieList) {

        cookieList->erase(cookieIterator);

        if ((cookieList->isEmpty()) &&
            (cookieList->getAdvice() == KCookieDunno))
        {

            delete m_cookieDomains.take(domain);
            m_domainList.removeAll(domain);
        }
    }
}
