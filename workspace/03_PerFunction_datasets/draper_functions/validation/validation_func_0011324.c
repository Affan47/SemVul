translated(double degreesLatitude, double degreesLongitude) const
{
    QGeoBoundingBox result(*this);
    result.translate(degreesLatitude, degreesLongitude);
    return result;
}
