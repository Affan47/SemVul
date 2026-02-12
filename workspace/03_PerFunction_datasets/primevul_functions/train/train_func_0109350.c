generate_hash_secret_salt(XML_Parser parser)
{


  const unsigned long entropy =
      gather_time_entropy() ^ getpid() ^ (unsigned long)parser;


  if (sizeof(unsigned long) == 4) {
    return entropy * 2147483647;
  } else {
    return entropy * 2305843009213693951;
  }
}
