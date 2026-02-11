main(int argc, char* argv[])
{
  try
  {
    cxxtools::Arg<const char*> fname(argc, argv, 'f');
    cxxtools::Arg<unsigned> mode(argc, argv, 'm', 0644);

    cxxtools::UuencodeOstream out(std::cout);

    if (fname)
      out.begin(fname.getValue(), mode);

    out << std::cin.rdbuf();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
