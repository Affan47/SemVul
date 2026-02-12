QPDFObjectHandle::isPageObject()
{

    if (! this->isDictionary())
    {
        return false;
    }
    if (this->hasKey("/Type"))
    {
        QPDFObjectHandle type = this->getKey("/Type");
        if (type.isName() && (type.getName() == "/Page"))
        {
            return true;
        }

        if (type.isString() && (type.getStringValue() == "Page"))
        {
            return true;
        }
    }
    if (this->hasKey("/Contents"))
    {
        return true;
    }
    return false;
}
