channelImageReady( Podcasts::PodcastChannelPtr channel, QImage image )
{
    if( image.isNull() )
        return;

    channel->setImage( image );
}
