numHrZones()
{
    int hr_zone_range = hrZoneRange();
    return (hr_zone_range >= 0) ? hrZones->numZones(hr_zone_range) : 0;
}
