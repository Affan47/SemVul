buttonpressed(int         id)
{
    tstringselect::buttonpressed(id);
    switch (id) {

    case 12:
        if ( redline >= 0 )
            action = id-10;
        break;

    case 13:
        action = id-10;
        break;
    }
}
