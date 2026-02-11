GetRefcount() const
{
    int extra=0;


    if (id > 0 && static_cast<nNetObject*>(sn_netObjects[id])==this)
    {
        if ( createdLocally )
            extra = -1;
    }


    return this->refCtr_ + extra;
}
