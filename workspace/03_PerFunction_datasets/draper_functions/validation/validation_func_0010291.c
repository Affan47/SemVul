algo_available( preftype_t preftype, int algo, const union pref_hint *hint )
{
  if( preftype == PREFTYPE_SYM )
    {
      if(PGP6 && (algo != CIPHER_ALGO_IDEA
		  && algo != CIPHER_ALGO_3DES
		  && algo != CIPHER_ALGO_CAST5))
	return 0;

      if(PGP7 && (algo != CIPHER_ALGO_IDEA
		  && algo != CIPHER_ALGO_3DES
		  && algo != CIPHER_ALGO_CAST5
		  && algo != CIPHER_ALGO_AES
		  && algo != CIPHER_ALGO_AES192
		  && algo != CIPHER_ALGO_AES256
		  && algo != CIPHER_ALGO_TWOFISH))
	return 0;


      return algo && !check_cipher_algo( algo );
    }
  else if( preftype == PREFTYPE_HASH )
    {
      if(hint && hint->digest_length)
	{
	  if(hint->digest_length!=20 || opt.flags.dsa2)
	    {


	      if(hint->digest_length > md_digest_length(algo))
		return 0;
	    }
	  else if(hint->digest_length != md_digest_length(algo))
	    return 0;
	}

      if((PGP6 || PGP7) && (algo != DIGEST_ALGO_MD5
			    && algo != DIGEST_ALGO_SHA1
			    && algo != DIGEST_ALGO_RMD160))
	return 0;


      if(PGP8 && (algo != DIGEST_ALGO_MD5
		  && algo != DIGEST_ALGO_SHA1
		  && algo != DIGEST_ALGO_RMD160
		  && algo != DIGEST_ALGO_SHA256))
	return 0;

      return algo && !check_digest_algo( algo );
    }
  else if( preftype == PREFTYPE_ZIP )
    {
      if((PGP6 || PGP7) && (algo != COMPRESS_ALGO_NONE
			    && algo != COMPRESS_ALGO_ZIP))
	return 0;


      return !check_compress_algo( algo );
    }
  else
    return 0;
}
