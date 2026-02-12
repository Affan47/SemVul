std::ostream& LangAltValue::write(std::ostream& os) const
    {
        bool        first     = true;


        ValueType::const_iterator i = value_.find(x_default);
        if (i != value_.end()) {
            os << "lang=\"" << i->first << "\" " << i->second;
            first = false;
        }


        for (i = value_.begin(); i != value_.end(); ++i) {
            if (i->first != x_default ) {
                if (!first) os << ", ";
                os << "lang=\"" << i->first << "\" " << i->second;
                first = false;
            }
        }
        return os;
    }
