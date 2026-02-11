DataToString(const SqlStmtFieldData& data, std::ostringstream& fmt)
{
    switch (data.type())
    {
        case FIELD_BOOL:    fmt << "'" << uint32(data.toBool()) << "'";     break;
        case FIELD_UI8:     fmt << "'" << uint32(data.toUint8()) << "'";    break;
        case FIELD_UI16:    fmt << "'" << uint32(data.toUint16()) << "'";   break;
        case FIELD_UI32:    fmt << "'" << data.toUint32() << "'";           break;
        case FIELD_UI64:    fmt << "'" << data.toUint64() << "'";           break;
        case FIELD_I8:      fmt << "'" << int32(data.toInt8()) << "'";      break;
        case FIELD_I16:     fmt << "'" << int32(data.toInt16()) << "'";     break;
        case FIELD_I32:     fmt << "'" << data.toInt32() << "'";            break;
        case FIELD_I64:     fmt << "'" << data.toInt64() << "'";            break;
        case FIELD_FLOAT:   fmt << "'" << data.toFloat() << "'";            break;
        case FIELD_DOUBLE:  fmt << "'" << data.toDouble() << "'";           break;
        case FIELD_STRING:
        {
            std::string tmp = data.toStr();
            m_pConn.DB().escape_string(tmp);
            fmt << "'" << tmp << "'";
            break;
        }
        case FIELD_NONE:                                                    break;
    }
}
