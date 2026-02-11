addElementToDataset(OFCondition &result,
                                          DcmItem &dataset,
                                          DcmElement *delem,
                                          const OFString &vm,
                                          const OFString &type,
                                          const char *moduleName)
{
    if (delem != NULL)
    {
        OFBool triedToInsert = OFFalse;
        if (result.good())
        {
            if ((type == "2") || !delem->isEmpty())
            {
                triedToInsert = OFTrue;

                result = dataset.insert(delem, OFTrue );
                if (DCM_dcmsrGetLogger().isEnabledFor(OFLogger::WARN_LOG_LEVEL))
                    checkElementValue(*delem, vm, type, result, moduleName);
            }
            else if (type == "1")
            {

                result = SR_EC_InvalidValue;
                if (DCM_dcmsrGetLogger().isEnabledFor(OFLogger::WARN_LOG_LEVEL))
                    checkElementValue(*delem, vm, type, result, moduleName);
            }
        }

        if (result.bad() || !triedToInsert)
            delete delem;
    } else
        result = EC_MemoryExhausted;
    return result;
}
