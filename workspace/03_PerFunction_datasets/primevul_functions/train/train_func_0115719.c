Exifdatum& Exifdatum::operator=(const Exifdatum& rhs)
    {
        if (this == &rhs) return *this;
        Metadatum::operator=(rhs);

        key_.reset();
        if (rhs.key_.get() != 0) key_ = rhs.key_->clone();

        value_.reset();
        if (rhs.value_.get() != 0) value_ = rhs.value_->clone();

        return *this;
    }
