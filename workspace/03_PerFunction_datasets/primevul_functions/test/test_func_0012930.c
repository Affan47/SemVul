static void reds_migrate_channels_seamless(RedsState *reds)
{
    RedClient *client;


    client = reds_get_client(reds);
    client->migrate();
}
