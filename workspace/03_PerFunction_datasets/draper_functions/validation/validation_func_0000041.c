operator>>(QDataStream& in, QOrganizerItemFilter& filter)
{
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        quint32 type;
        in >> type;
        switch (type) {
            case QOrganizerItemFilter::InvalidFilter:
                filter = QOrganizerItemInvalidFilter();
                break;
            case QOrganizerItemFilter::OrganizerItemDetailFilter:
                filter = QOrganizerItemDetailFilter();
                break;
            case QOrganizerItemFilter::OrganizerItemDetailRangeFilter:
                filter = QOrganizerItemDetailRangeFilter();
                break;
            case QOrganizerItemFilter::ChangeLogFilter:
                filter = QOrganizerItemChangeLogFilter();
                break;
            case QOrganizerItemFilter::IntersectionFilter:
                filter = QOrganizerItemIntersectionFilter();
                break;
            case QOrganizerItemFilter::UnionFilter:
                filter = QOrganizerItemUnionFilter();
                break;
            case QOrganizerItemFilter::IdFilter:
                filter = QOrganizerItemIdFilter();
                break;
            case QOrganizerItemFilter::DefaultFilter:
                filter = QOrganizerItemFilter();
                break;
        }

        if (filter.d_ptr) {
            filter.d_ptr->inputFromStream(in, formatVersion);
        }
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
