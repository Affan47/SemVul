supportedMedia() const
{
    Solid::OpticalDrive::MediumTypes supported;

    QMap<Solid::OpticalDrive::MediumType, QString> map;
    map[Solid::OpticalDrive::Cdr] = "storage.cdrom.cdr";
    map[Solid::OpticalDrive::Cdrw] = "storage.cdrom.cdrw";
    map[Solid::OpticalDrive::Dvd] = "storage.cdrom.dvd";
    map[Solid::OpticalDrive::Dvdr] = "storage.cdrom.dvdr";
    map[Solid::OpticalDrive::Dvdrw] ="storage.cdrom.dvdrw";
    map[Solid::OpticalDrive::Dvdram] ="storage.cdrom.dvdram";
    map[Solid::OpticalDrive::Dvdplusr] ="storage.cdrom.dvdplusr";
    map[Solid::OpticalDrive::Dvdplusrw] ="storage.cdrom.dvdplusrw";
    map[Solid::OpticalDrive::Dvdplusdl] ="storage.cdrom.dvdplusrdl";
    map[Solid::OpticalDrive::Dvdplusdlrw] ="storage.cdrom.dvdplusrwdl";
    map[Solid::OpticalDrive::Bd] ="storage.cdrom.bd";
    map[Solid::OpticalDrive::Bdr] ="storage.cdrom.bdr";
    map[Solid::OpticalDrive::Bdre] ="storage.cdrom.bdre";
    map[Solid::OpticalDrive::HdDvd] ="storage.cdrom.hddvd";
    map[Solid::OpticalDrive::HdDvdr] ="storage.cdrom.hddvdr";
    map[Solid::OpticalDrive::HdDvdrw] ="storage.cdrom.hddvdrw";

    foreach (const Solid::OpticalDrive::MediumType type, map.keys())
    {
        if (m_device->prop(map[type]).toBool())
        {
            supported|= type;
        }
    }

    return supported;
}
