libcrypto_lock_callback(int mode, int i, const char *file, int line){
	(void)file;
	(void)line;
	if(mode & CRYPTO_LOCK){
		user_callbacks->mutex_lock(&libcrypto_mutexes[i]);
	} else {
		user_callbacks->mutex_unlock(&libcrypto_mutexes[i]);
	}
}
