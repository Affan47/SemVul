drawWallpaper() const
{
    Q_ASSERT(d->applet);
    Plasma::Containment *cont = qobject_cast<Plasma::Containment *>(d->applet);
    if (cont) {
        return cont->drawWallpaper();
    } else {
        return false;
    }
}
