usr_cache_hash_fn (const void *key)
{
    UserCacheObj *usrObj = (UserCacheObj *)key;

    if (usrObj->derCert)
	return usr_cache_hash_cert(usrObj->derCert);
    else
	return PR_HashCaseString(usrObj->uid);
}
