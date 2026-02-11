ff_read_sp_step( FL_OBJECT * obj  FL_UNUSED_ARG,
                 SuperSPEC * sp )
{
    int r;

    if (    (    obj->objclass == FL_SPINNER
              && ( r = ff_read( "%F", &sp->dstep ) ) < 0 )
         || (    obj->objclass != FL_SPINNER
              && ( r = ff_read( "%f", &sp->step ) ) < 0 ) )
        return ff_err( "Can't read expected object step" );

    if ( r == 0 )
        return ff_err( "\"step\" key with no or invalid value" );

    return 0;
}
