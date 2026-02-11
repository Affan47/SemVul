generic_factory(const std::string & name, int no)
{
    Operation::Generic obj;
    obj->setType(name, no);
    return obj;
}
