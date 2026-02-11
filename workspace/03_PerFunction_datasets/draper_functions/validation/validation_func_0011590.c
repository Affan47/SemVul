loadEcoFile(const QString& ecoFile)
{
    QFile file(ecoFile);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream sin(&file);
        quint32 id;
        sin >> id;
        if(id == COMPILED_GUESS_FILE_ID)
        {
            sin >> ecoGuessPositions;
        }
        return true;
    }
    return false;
}
