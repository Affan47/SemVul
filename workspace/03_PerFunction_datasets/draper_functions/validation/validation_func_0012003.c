start()
{
    if( this->state() == Ready || this->state() == Finished )
    {
        _state = Thread::Running;
        _impl->start();
    }
}
