localconnection_new(const fn_call& fn)
{

    as_object* obj = ensure<ValidThis>(fn);
    obj->setRelay(new LocalConnection_as(obj));
    return as_value();
}
