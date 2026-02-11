indentation_count(boost::string_ref x)
    {
        unsigned count = 0;

        for(boost::string_ref::const_iterator begin = x.begin(), end = x.end();
            begin != end; ++begin)
        {
            switch(*begin)
            {
            case ' ':
                ++count;
                break;
            case '\t':

                count = count - (count % 4) + 4;
                break;
            default:
                assert(false);
            }
        }

        return count;
    }
