main(int argc, char* argv[])
{


  std::locale::global(std::locale(""));

  std::string filepath;
  if(argc > 1 )
    filepath = argv[1];
  else
    filepath = "example.xml";


  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  try
  {
  #endif
    MySaxParser parser;
    parser.set_substitute_entities(true);
    parser.parse_file(filepath);
  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  }
  catch(const xmlpp::exception& ex)
  {
    std::cout << "libxml++ exception: " << ex.what() << std::endl;
  }
  #endif


  {


    std::ifstream is(filepath.c_str());


    MySaxParser parser;
    parser.parse_file(filepath);


  }


  return 0;
}
