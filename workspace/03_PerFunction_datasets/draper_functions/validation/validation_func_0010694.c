textIcon() const
{
    Q_D( const TextAnnotation );

    if (!d->pdfAnnot)
        return d->textIcon;

    if (d->pdfAnnot->getType() == Annot::typeText)
    {
        const AnnotText * textann = static_cast<const AnnotText*>(d->pdfAnnot);
        return QString::fromLatin1( textann->getIcon()->getCString() );
    }

    return QString();
}
