startParsing(XML_Parser parser)
{

    if (hash_secret_salt == 0)
      hash_secret_salt = generate_hash_secret_salt(parser);
    if (ns) {


      return setContext(parser, implicitContext);
    }
    return XML_TRUE;
}
