addHeader(const std::string& name,
				     const std::string& value)
{
  fHeaders.push_back(name + ": " + value);
  return *this;
}
