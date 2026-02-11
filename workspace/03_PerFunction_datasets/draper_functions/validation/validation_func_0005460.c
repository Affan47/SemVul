LoadConfig() {
    if( !game ) return false;

    cJSON *root = NULL, *item = NULL;
    char *json_file = NULL;

    bool return_val = false;

    Byte_ReadFile( &json_file, config_file );
    check( json_file, "Error when loading config file!\n" );

    root = cJSON_Parse( json_file );
    check( root, "JSON Parse error [%s] before :\n%s\n", config_file, cJSON_GetErrorPtr() );


    if( !LoadConfigItem( root, &item, "bFullscreen" ) )
        game->config.fullscreen = 0;
    else
        game->config.fullscreen = item->type > 0;


    if( !LoadConfigItem( root, &item, "iWindowWidth" ) )
        game->config.window_size.x = 800;
    else
        game->config.window_size.x = (f32)item->valueint;

    if( !LoadConfigItem( root, &item, "iWindowHeight" ) )
        game->config.window_size.y = 600;
    else
        game->config.window_size.y = (f32)item->valueint;


    if( !LoadConfigItem( root, &item, "iMultiSamples" ) )
        game->config.multisamples = 0;
    else
        game->config.multisamples = item->valueint;

    return_val = true;

error:
    DEL_PTR( json_file );
    if( root ) cJSON_Delete( root );
    return return_val;
}
