init()
    {
        m_fontInfoIterator = 0;
        m_backend = Document::SplashBackend;
        paperColor = Qt::white;
        m_hints = 0;
        m_optContentModel = 0;

        if ( count == 0 )
        {
            utf8Map = 0;
            globalParams = new GlobalParams();
            setErrorCallback(qt4ErrorFunction, NULL);
        }
        count ++;
    }
