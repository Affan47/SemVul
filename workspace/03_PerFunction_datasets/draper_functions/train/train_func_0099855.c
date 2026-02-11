st_LoadConfig( bool printChange )
{

    tCurrentAccessLevel level( tAccessLevel_Owner, true );

    st_InstallSigHupHandler();

    const tPath& var = tDirectories::Var();
    const tPath& config = tDirectories::Config();
    const tPath& data = tDirectories::Data();

    tConfItemBase::printChange=printChange;
#ifdef DEDICATED
    tConfItemBase::printErrors=false;
#endif
    {
        Load( var, "user.cfg" );
    }
    tConfItemBase::printErrors=true;

    Load( config, "settings.cfg" );
#ifdef DEDICATED
    Load( config, "settings_dedicated.cfg" );
    if( extraConfig != "NONE" ) Load( config, extraConfig );
#else
    if (st_FirstUse)
    {
        Load( config, "default.cfg" );
    }
#endif

    Load( data, "moviepack/settings.cfg" );

    Load( config, "autoexec.cfg" );
    Load( var, "autoexec.cfg" );


    tConfItemBase::LoadPlayback();
    st_settingsFromRecording = tRecorder::IsPlayingBack();

    tConfItemBase::printChange=true;
}
