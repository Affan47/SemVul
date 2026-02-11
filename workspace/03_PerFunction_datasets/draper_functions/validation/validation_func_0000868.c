print0x0527(std::ostream& os, const Value& value, const ExifData*)
    {
        if (   value.count() != 3
               || value.typeId() != signedShort
               || value.toLong(1) != -2
               || value.toLong(2) != 1) {
            return os << value;
        }

        switch (value.toLong(0)) {
            case -2: os << _("Off"); break;
            case -1: os << _("Low"); break;
            case  0: os << _("Standard"); break;
            case  1: os << _("High"); break;
            default: os << value.toLong(0); break;
        }

        return os;
    }
