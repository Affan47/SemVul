bool TemporaryFile::deleteTemporaryFile() const
{

    for (int i = 5; --i >= 0;)
    {
        if (temporaryFile.isDirectory() ? temporaryFile.deleteRecursively() : temporaryFile.deleteFile())
            return true;

        Thread::sleep (50);
    }

    return false;
}
