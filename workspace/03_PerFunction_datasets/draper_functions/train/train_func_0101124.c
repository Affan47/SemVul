pop_front(string & arg)
    {
        if(relative)
            if(dirs.size() > 1)
            {
                arg = dirs.front();
                dirs.pop_front();
                return true;
            }
            else
                return false;
        else
            if(!dirs.empty())
            {
                relative = false;
                arg = "/";
                return true;
            }
            else
                return false;
    }
