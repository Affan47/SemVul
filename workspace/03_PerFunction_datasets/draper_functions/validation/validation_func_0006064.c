getCustomProperty(const QWidget *widget) const
{
    QVariant prop(widget->property("kcfg_property"));
    if (prop.isValid()) {
        if (!prop.canConvert(QVariant::ByteArray)) {
            kWarning(d->debugArea()) << "kcfg_property on" << widget->metaObject()->className()
                          << "is not of type ByteArray";
        } else {
            return prop.toByteArray();
        }
    }
    return QByteArray();
}
