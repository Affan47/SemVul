toVar() const
{

    ConfigVar out;
    out.writeInt( vars.size() );
    map<string, ConfigVar>::const_iterator it;
    for(it = vars.begin(); it != vars.end(); ++it)
    {
	out.writeInt( it->first.size() );
	out.write( (unsigned char*)it->first.data(), it->first.size() );
	out.writeInt( it->second.size() );
	out.write( (unsigned char*)it->second.buffer(), it->second.size() );
    }

    return out;
}
