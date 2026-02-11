closeAll()
{
    QList<MainWindow *> windows = mainwindows;

    foreach(MainWindow *window, windows)
        if (window != this) window->close();


    close();
}
