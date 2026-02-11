emitFilesChanged(const QStringList &fileList)
{
    emitSignal(QLatin1String("FilesChanged"), QVariantList() << QVariant(fileList));
}
