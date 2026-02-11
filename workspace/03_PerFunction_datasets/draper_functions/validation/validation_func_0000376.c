setIntegerValue (const std::string &section,
                              const std::string &name,
                              int value)
{
    std::stringstream ss;
    ss << value;
    setStringValue (section, name, ss.str ());
}
