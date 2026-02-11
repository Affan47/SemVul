Pa_GetDefaultInputDevice( void )
{
    PaHostApiIndex hostApi;
    PaDeviceIndex result;

    PA_LOGAPI_ENTER( "Pa_GetDefaultInputDevice" );

    hostApi = Pa_GetDefaultHostApi();
    if( hostApi < 0 )
    {
        result = paNoDevice;
    }
    else
    {
        result = paInternalInfo_.hostApis_[hostApi]->info.defaultInputDevice;
    }

    PA_LOGAPI_EXIT_T( "Pa_GetDefaultInputDevice", "PaDeviceIndex: %d", result );

    return result;
}
