operator=( const CbcSimpleInteger & rhs)
{
    if (this != &rhs) {
        CbcObject::operator=(rhs);
        columnNumber_ = rhs.columnNumber_;
        originalLower_ = rhs.originalLower_;
        originalUpper_ = rhs.originalUpper_;
        breakEven_ = rhs.breakEven_;
        preferredWay_ = rhs.preferredWay_;
    }
    return *this;
}
