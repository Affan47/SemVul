nextButtonClicked()
{


    switch (currentPage() + m_pageOffset)
    {
        case 0:
        {

        }
        break;

        case 1:
        {

            QApplication::setOverrideCursor( Qt::WaitCursor );
            m_page2->verify();


            enableNext(false);
            enableBack(false);
            return;
        }
        break;

        case 2:
        {

            mAvailPlugins.clear();
            m_infoGetter.GetUpdateInfo(NULL, &mAvailPlugins, true);
        }
        break;

        case 3:
        {

            BaseWizard::nextButtonClicked();
            m_page5->Populate(mAvailPlugins);
            return;
        }
        break;

        case 4:
        {

            BaseWizard::nextButtonClicked();
            if (!downloadPlugins())
            {
                BaseWizard::backButtonClicked();
            }
            return;
        }
        break;

        case 5:
        {

        }
        break;

        case 6:
        {


            if ( m_page7 && m_page7->selectedPlugin() != NULL )
            {
                CPluginInfo* bootstrapPlugin = m_page7->selectedPlugin();

                if( !bootstrapPlugin )
                {
                    nextButtonClicked();
                    return;
                }

                #ifndef Q_WS_X11
                switch( bootstrapPlugin->GetBootstrapType() )
                {
                case CPluginInfo::BOOTSTRAP_CLIENT:
                    if( bootstrapPlugin->GetPlayerName() == "iTunes" )
                    {
                        m_bootstrapper = new iTunesBootstrapper();
                    }
                    else
                    {
                        Q_ASSERT( !"No clientside bootstrapper implemented for this mediaplayer yet." );
                    }
                    break;

                case CPluginInfo::BOOTSTRAP_PLUGIN:
                    m_bootstrapper = new PluginBootstrapper( bootstrapPlugin->GetId() );
                    m_didBootstrap = true;
                    m_bootstrapStatus = AbstractBootstrapper::Bootstrap_Ok;
                    break;

                default:
                    Q_ASSERT( !"not possible" );
                }

                setNumPages( numPages() - 1 );
                m_pageOffset++;

                if ( m_page7->selectedPlugin()->GetBootstrapType() == CPluginInfo::BOOTSTRAP_PLUGIN )
                {
                    setNumPages( numPages() - 1 );
                    m_pageOffset++;
                }

                nextButtonClicked();

                m_bootstrapper->bootStrap();

                if( !dynamic_cast<AbstractFileBootstrapper*>( m_bootstrapper ) )
                {
                    onBootstrapDone( AbstractBootstrapper::Bootstrap_Ok );
                }
                #endif

                return;
            }
            else
            {
                setNumPages( numPages() - 2 );
                m_pageOffset += 2;
            }
        }
        break;

        case 7:
        break;

        case 8:
        {

        }
        break;

        case 9:
        {

        }
        break;

        case 10:
        {

        }
        break;

        default:
            Q_ASSERT( !"duh" );

    }

    BaseWizard::nextButtonClicked();

}
