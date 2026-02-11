close()
{
  if (!tag.empty())
  {
    out << "</";

    std::string::size_type p = tag.find(' ');
    if (p != std::string::npos)
      out.write(tag.data(), p);
    else
      out << tag;

    out << '>';

    tag.clear();
  }
}
