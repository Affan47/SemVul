put (ogzstream & file) const
{
    u_int16 i;

    fileops::put_version (file, 1);


    nbr_of_animations () >> file;
    for (i = 0; i < nbr_of_animations (); i++)
    {
        anim[i]->put (file);
    }

    mapsquare_walkable_area::put (file);

    return 0;
}
