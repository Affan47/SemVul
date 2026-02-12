SQInstance::~SQInstance()
{
    REMOVE_FROM_CHAIN(&_sharedstate->_gc_chain, this);
    if(_class){ Finalize(); }
}
