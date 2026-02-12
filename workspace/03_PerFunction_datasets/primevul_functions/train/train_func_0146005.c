HandleARDAuth(rfbClient *client)
{
  uint8_t gen[2], len[2];
  size_t keylen;
  uint8_t *mod = NULL, *resp = NULL, *priv = NULL, *pub = NULL, *key = NULL, *shared = NULL;
  uint8_t userpass[128], ciphertext[128];
  int ciphertext_len;
  int passwordLen, usernameLen;
  rfbCredential *cred = NULL;
  rfbBool result = FALSE;


  if (!ReadFromRFBServer(client, (char *)gen, 2)) {
      rfbClientErr("HandleARDAuth: reading generator value failed\n");
      goto out;
  }
  if (!ReadFromRFBServer(client, (char *)len, 2)) {
      rfbClientErr("HandleARDAuth: reading key length failed\n");
      goto out;
  }
  keylen = 256*len[0]+len[1];

  mod = (uint8_t*)malloc(keylen*5);
  if (!mod)
      goto out;

  resp = mod+keylen;
  pub = resp+keylen;
  priv = pub+keylen;
  key = priv+keylen;


  if (!ReadFromRFBServer(client, (char *)mod, keylen)) {
      rfbClientErr("HandleARDAuth: reading prime modulus failed\n");
      goto out;
  }
  if (!ReadFromRFBServer(client, (char *)resp, keylen)) {
      rfbClientErr("HandleARDAuth: reading peer's generated public key failed\n");
      goto out;
  }


  if(!dh_generate_keypair(priv, pub, gen, 2, mod, keylen)) {
      rfbClientErr("HandleARDAuth: generating keypair failed\n");
      goto out;
  }


  if(!dh_compute_shared_key(key, priv, resp, mod, keylen)) {
      rfbClientErr("HandleARDAuth: creating shared key failed\n");
      goto out;
  }


  shared = malloc(MD5_HASH_SIZE);
  if(!hash_md5(shared, key, keylen)) {
      rfbClientErr("HandleARDAuth: hashing shared key failed\n");
      goto out;
  }


  if(!client->GetCredential) {
      rfbClientErr("HandleARDAuth: GetCredential callback is not set\n");
      goto out;
  }
  cred = client->GetCredential(client, rfbCredentialTypeUser);
  if(!cred) {
      rfbClientErr("HandleARDAuth: reading credential failed\n");
      goto out;
  }
  passwordLen = strlen(cred->userCredential.password)+1;
  usernameLen = strlen(cred->userCredential.username)+1;
  if (passwordLen > sizeof(userpass)/2)
      passwordLen = sizeof(userpass)/2;
  if (usernameLen > sizeof(userpass)/2)
      usernameLen = sizeof(userpass)/2;
  random_bytes(userpass, sizeof(userpass));
  memcpy(userpass, cred->userCredential.username, usernameLen);
  memcpy(userpass+sizeof(userpass)/2, cred->userCredential.password, passwordLen);


  if(!encrypt_aes128ecb(ciphertext, &ciphertext_len, shared, userpass, sizeof(userpass))) {
      rfbClientErr("HandleARDAuth: encrypting credentials failed\n");
      goto out;
  }


  if (!WriteToRFBServer(client, (char *)ciphertext, sizeof(ciphertext)))
      goto out;
  if (!WriteToRFBServer(client, (char *)pub, keylen))
      goto out;


  if (!rfbHandleAuthResult(client))
      goto out;

  result = TRUE;

 out:
  if (cred)
    FreeUserCredential(cred);

  free(mod);
  free(shared);

  return result;
}
