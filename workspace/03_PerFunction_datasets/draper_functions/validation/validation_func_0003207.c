operator>>(std::string &fMessage)
    {
        register int fResult = Recv();
        fMessage = "";

        for (register int i = 0; i < fBufLength; i++)
            fMessage += fBuf[i];

        return fResult;
    }
