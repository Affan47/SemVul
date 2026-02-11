checkInputFile()
{
    string base(_fileName);
    string suffix;
    string::size_type pos = base.rfind('.');
    if(pos != string::npos)
    {
        suffix = IceUtilInternal::toLower(base.substr(pos));
    }
    if(suffix != ".ice")
    {
        getErrorStream() << _path << ": error: input files must end with `.ice'" << endl;
        return false;
    }

    ifstream test(_fileName.c_str());
    if(!test)
    {
        getErrorStream() << _path << ": error: cannot open `" << _fileName << "' for reading" << endl;
        return false;
    }
    test.close();

    return true;
}
