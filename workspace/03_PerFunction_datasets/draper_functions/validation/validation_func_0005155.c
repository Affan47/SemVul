convertArrayToList( KJS::ExecState *exec, KJS::JSValue *value )
{
    QList<QVariant> returnList;


    KJS::ArrayInstance* arrayImp = extractBindingImp<KJS::ArrayInstance>(exec, value);
    if(arrayImp)
    {
        const unsigned numItems = arrayImp->getLength();
        for ( unsigned i = 0; i < numItems; ++i )
            returnList.append( convertToVariant(exec, arrayImp->getItem(i)) );
    }
    return returnList;
}
