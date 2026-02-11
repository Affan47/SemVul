navigateLocalProtocol( khtml::ChildFrame* , KParts::ReadOnlyPart *inPart,
                                       const KUrl& url )
{
    if (!qobject_cast<KHTMLPart*>(inPart))
        return false;

    KHTMLPart* p = static_cast<KHTMLPart*>(static_cast<KParts::ReadOnlyPart *>(inPart));

    p->begin();


    d->propagateInitialDomainAndBaseTo(p);


    if (d->isJavaScriptURL(url.url())) {

        QVariant res = p->executeScript( DOM::Node(),
                                        d->codeForJavaScriptURL(url.url()));
        if (res.type() == QVariant::String && p->d->m_redirectURL.isEmpty()) {
            p->begin();
            p->setAlwaysHonourDoctype();

            d->propagateInitialDomainAndBaseTo(p);
            p->write( res.toString() );
            p->end();
        }
    } else {
        p->setUrl(url);

        p->write("<HTML><TITLE></TITLE><BODY></BODY></HTML>");
    }
    p->end();


    return true;
}
