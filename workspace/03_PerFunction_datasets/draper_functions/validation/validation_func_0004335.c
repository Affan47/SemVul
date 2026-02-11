delattr(object const& target, char const* key)
{
    if (PyObject_DelAttrString(
            target.ptr(), const_cast<char*>(key)) == -1
        )
    {
        throw_error_already_set();
    }
}
