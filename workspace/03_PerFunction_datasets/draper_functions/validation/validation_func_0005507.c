operator=(List &list)
{
    Destroy();
    list.Start_Get();
    Object	*obj;
    while ((obj = list.Get_Next()))
    {
	Add(obj->Copy());
    }
    return *this;
}
