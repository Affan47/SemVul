operator<(const Identity& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    if(category < __rhs.category)
    {
        return true;
    }
    else if(__rhs.category < category)
    {
        return false;
    }
    return false;
}
