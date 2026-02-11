themeChanged()
{
    if (q->imagePath().isEmpty()) {
        return;
    }

    if (themed) {

        checkColorHints();
    }

    QString currentPath = themed ? themePath : path;
    themePath.clear();
    eraseRenderer();
    setImagePath(currentPath);


    emit q->repaintNeeded();
}
