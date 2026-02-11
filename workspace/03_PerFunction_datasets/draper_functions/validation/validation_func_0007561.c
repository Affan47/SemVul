openFile(const QString &path)
{
    media->setCurrentSource(Phonon::MediaSource(path));
    media->play();
}
