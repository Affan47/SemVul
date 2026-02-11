register_bool(const std::string& name, bool defval)
{
    if (data.find(name) != data.end())
    {
        return false;
    }
    libmormegil::Appcfg::Entry e;
    e.bval = defval;
    e.t = Appcfg_boolean;
    data[name] = e;
    return true;
}
