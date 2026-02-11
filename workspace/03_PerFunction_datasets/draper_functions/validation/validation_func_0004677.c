findTest(const std::string& name)
{
    Tests::iterator it;
    for (it = _tests.begin(); it != _tests.end() && it->first != name; ++it)
        ;

    if( it== _tests.end() )
        return 0;

    return it->second;
}
