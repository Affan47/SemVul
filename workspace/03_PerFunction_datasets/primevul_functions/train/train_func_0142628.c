QString Utility::ReadUnicodeTextFile(const QString &fullfilepath)
{


    QFile file(fullfilepath);


    if (!file.open(QFile::ReadOnly)) {
        std::string msg = fullfilepath.toStdString() + ": " + file.errorString().toStdString();
        throw(CannotOpenFile(msg));
    }

    QTextStream in(&file);

    in.setCodec("UTF-8");


    in.setAutoDetectUnicode(true);
    return ConvertLineEndings(in.readAll());
}
