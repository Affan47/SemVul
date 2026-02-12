int PasswdMgr::readPasswdFileData(std::vector<uint8_t>& outBytes)
{
    std::array<uint8_t, maxKeySize> keyBuff;
    std::ifstream keyFile(encryptKeyFileName, std::ios::in | std::ios::binary);
    if (!keyFile.is_open())
    {
        log<level::DEBUG>("Error in opening encryption key file");
        return -EIO;
    }
    keyFile.read(reinterpret_cast<char*>(keyBuff.data()), keyBuff.size());
    if (keyFile.fail())
    {
        log<level::DEBUG>("Error in reading encryption key file");
        return -EIO;
    }

    std::ifstream passwdFile(passwdFileName, std::ios::in | std::ios::binary);
    if (!passwdFile.is_open())
    {
        log<level::DEBUG>("Error in opening ipmi password file");
        return -EIO;
    }


    passwdFile.seekg(0, std::ios::end);
    ssize_t fileSize = passwdFile.tellg();
    passwdFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> input(fileSize);
    passwdFile.read(reinterpret_cast<char*>(input.data()), fileSize);
    if (passwdFile.fail())
    {
        log<level::DEBUG>("Error in reading encryption key file");
        return -EIO;
    }


    MetaPassStruct* metaData = reinterpret_cast<MetaPassStruct*>(input.data());
    if (std::strncmp(metaData->signature, META_PASSWD_SIG,
                     sizeof(metaData->signature)))
    {
        log<level::DEBUG>("Error signature mismatch in password file");
        return -EBADMSG;
    }

    size_t inBytesLen = metaData->dataSize + metaData->padSize;

    if (inBytesLen == 0)
    {
        log<level::DEBUG>("Empty password file");
        return 0;
    }


    std::array<uint8_t, EVP_MAX_KEY_LENGTH> key;
    auto keyLen = key.size();
    if (NULL == HMAC(EVP_sha256(), keyBuff.data(), keyBuff.size(),
                     input.data() + sizeof(*metaData), metaData->hashSize,
                     key.data(), reinterpret_cast<unsigned int*>(&keyLen)))
    {
        log<level::DEBUG>("Failed to create MAC for authentication");
        return -EIO;
    }


    uint8_t* iv = input.data() + sizeof(*metaData) + metaData->hashSize;
    size_t ivLen = metaData->ivSize;
    uint8_t* inBytes = iv + ivLen;
    uint8_t* mac = inBytes + inBytesLen;
    size_t macLen = metaData->macSize;

    size_t outBytesLen = 0;

    outBytes.resize(inBytesLen + EVP_MAX_BLOCK_LENGTH);
    if (encryptDecryptData(false, EVP_aes_128_cbc(), key.data(), keyLen, iv,
                           ivLen, inBytes, inBytesLen, mac, &macLen,
                           outBytes.data(), &outBytesLen) != 0)
    {
        log<level::DEBUG>("Error in decryption");
        return -EIO;
    }

    outBytes.resize(outBytesLen);

    OPENSSL_cleanse(key.data(), keyLen);
    OPENSSL_cleanse(iv, ivLen);

    return 0;
}
