ReportStreamTime( PaStream *stream, paTestData *data )
{
    PaTime  streamTime, latency, outTime;

    streamTime = Pa_GetStreamTime( stream );
    outTime = data->outTime;
    if( outTime < 0.0 )
    {
        printf("Stream time = %8.1f\n", streamTime );
    }
    else
    {
        latency = outTime - streamTime;
        printf("Stream time = %8.4f, outTime = %8.4f, latency = %8.4f\n",
            streamTime, outTime, latency );
    }
    fflush(stdout);
}
