bool TemporaryFile::overwriteTargetFileWithTemporary() const
{


    jassert (targetFile != File());

    if (temporaryFile.exists())
    {

        for (int i = 5; --i >= 0;)
        {
            if (temporaryFile.replaceFileIn (targetFile))
                return true;

            Thread::sleep (100);
        }
    }
    else
    {


        jassertfalse;
    }

    return false;
}
