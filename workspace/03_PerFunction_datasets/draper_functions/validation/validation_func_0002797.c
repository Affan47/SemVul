findAndGetSint32Array(const DcmTagKey& tagKey,
                                           const Sint32 *&value,
                                           unsigned long *count,
                                           const OFBool searchIntoSub)
{
    DcmElement *elem;

    OFCondition status = findAndGetElement(tagKey, elem, searchIntoSub);
    if (status.good())
    {

        Sint32 *array = NULL;
        status = elem->getSint32Array(array);
        value = array;
    }

    if (count != NULL)
    {
        if (status.good())
            *count = elem->getLength() / sizeof(Sint32);
        else
            *count = 0;
    }

    if (status.bad())
        value = NULL;
    return status;
}
