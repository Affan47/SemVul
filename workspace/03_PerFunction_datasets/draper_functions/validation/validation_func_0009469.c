registerProcedure(const std::string& name, ServiceProcedure* proc)
{
    ProcedureMap::iterator it = _procedures.find(name);
    if (it == _procedures.end())
    {
        std::pair<const std::string, ServiceProcedure*> p( name, proc );
        _procedures.insert( p );
    }
    else
    {
        delete it->second;
        it->second = proc;
    }
}
