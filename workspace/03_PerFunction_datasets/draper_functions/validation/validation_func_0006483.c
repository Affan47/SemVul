onCancel()
{
    if (_impl->isConnected())
    {
        _impl->cancel();
    }
    else if (enabled())
    {

        _impl->close();
        setEnabled(false);
    }
}
