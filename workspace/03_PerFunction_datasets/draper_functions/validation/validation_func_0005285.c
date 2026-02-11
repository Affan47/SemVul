getSavedPropertyValue(const String& propertyName)
{
    PropertyValueMap::iterator it = d_savedPropertyValues.find(propertyName);

    if (it == d_savedPropertyValues.end())
    {


        savePropertyValue(propertyName);
        return getSavedPropertyValue(propertyName);
    }

    return it->second;
}
