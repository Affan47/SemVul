OutputPrivatekey(std::string &content, bool encryption, PasswordSource& passphrase) {
    BIO *out = BIO_new(BIO_s_mem());
    EVP_CIPHER *enc = NULL;
    if(!out) return false;
    if(rsa_key_ != NULL) {
      if(!encryption) {
        if(!PEM_write_bio_RSAPrivateKey(out,rsa_key_,enc,NULL,0,NULL,NULL)) {
          BIO_free_all(out); return false;
        }
      }
      else {
        enc = (EVP_CIPHER*)EVP_des_ede3_cbc();
        PW_CB_DATA cb_data;
        cb_data.password = &passphrase;
        if(!PEM_write_bio_RSAPrivateKey(out,rsa_key_,enc,NULL,0, &passwordcb,&cb_data)) {
          BIO_free_all(out); return false;
        }
      }
    }
    else if(pkey_ != NULL) {
      if(!encryption) {
        if(!PEM_write_bio_PrivateKey(out,pkey_,enc,NULL,0,NULL,NULL)) {
          BIO_free_all(out); return false;
        }
      }
      else {
        enc = (EVP_CIPHER*)EVP_des_ede3_cbc();
        PW_CB_DATA cb_data;
        cb_data.password = &passphrase;
        if(!PEM_write_bio_PrivateKey(out,pkey_,enc,NULL,0, &passwordcb,&cb_data)) {
          BIO_free_all(out); return false;
        }
      }
    }
    else {
      CredentialLogger.msg(ERROR, "Failed to get private key");
      BIO_free_all(out); return false;
    }

    for(;;) {
      char s[256];
      int l = BIO_read(out,s,sizeof(s));
      if(l <= 0) break;
      content.append(s,l);
    }
    BIO_free_all(out);
    return true;
  }
