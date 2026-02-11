writeV4Config( const char *configFile,
        const boost::shared_ptr<EncFSConfig> &config )
{
    ConfigReader cfg;

    cfg["cipher"] << config->cipherIface;
    cfg["keySize"] << config->keySize;
    cfg["blockSize"] << config->blockSize;
    string key;
    key.assign((char *)config->getKeyData(), config->keyData.size());
    cfg["keyData"] << key;

    return cfg.save( configFile );
}
