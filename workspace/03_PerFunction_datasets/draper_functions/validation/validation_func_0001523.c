refresh()
{
    if(instanceFlag)
    {
        delete single;
    }
    single = new Config();
    instanceFlag = true;
    if(!isParsed)
    {
        std::cout<<"Parsing failed!\n";
    }
    return single;
}
