traverse_flatten_cf_mg ( Object object )
{
    MultiGrid  flattened = NULL;
    int        position  = 0;
    int        i;
    Object     child, new_child;

    switch ( DXGetObjectClass ( object ) )
    {
        case CLASS_XFORM:
            if ( !DXGetXformInfo ( (Xform)object, &child, NULL ) ||
                 ( ERROR == ( new_child = traverse_flatten_cf_mg ( child ) ) ) )
                goto error;
            else if ( ( new_child != child ) &&
                      !DXSetXformObject ( (Xform)object, new_child ) )
                goto error;
            break;

        case CLASS_SCREEN:
            if ( !DXGetScreenInfo   ( (Screen)object, &child, NULL, NULL )  ||
                 ( ERROR == ( new_child = traverse_flatten_cf_mg ( child ) ) ) )
                goto error;
            else if ( ( new_child != child ) &&
                      !DXSetScreenObject ( (Screen)object, new_child ) )
                goto error;
            break;

        case CLASS_CLIPPED:
            if ( !DXGetClippedInfo    ( (Clipped)object, &child, NULL )     ||
                 ( ERROR == ( new_child = traverse_flatten_cf_mg ( child ) ) ) )
                goto error;
            else if ( ( new_child != child ) &&
                      !DXSetClippedObjects ( (Clipped)object, new_child, NULL ))
                goto error;
            break;

        case CLASS_GROUP:

            switch ( DXGetGroupClass ( (Group)object ) )
            {

                case CLASS_COMPOSITEFIELD:
                    for ( i     = 0;
                          NULL != ( child = DXGetEnumeratedMember
                                                ( (Group)object, i, NULL ) );
                          i++ )
                        if ( ( CLASS_GROUP     == DXGetObjectClass ( child ) )&&
                             ( CLASS_MULTIGRID == DXGetGroupClass
                                                      ( (Group) child ) ) )
                        {
                            position = 0;

                            if ( ( ERROR == ( flattened = DXNewMultiGrid () ) )
                                 ||
                                !flatten_cf_mg ( object, flattened, &position ))
                                goto error;


                            return (Object) flattened;
                            break;
                        }


                default:
                    for ( i     = 0;
                          NULL != ( child = DXGetEnumeratedMember
                                                ( (Group)object, i, NULL ) );
                          i++ )
                        if ( ERROR == ( new_child = traverse_flatten_cf_mg
                                                        ( child ) ) )
                            goto error;
                        else if ( ( new_child != child ) &&
                                  !DXSetEnumeratedMember
                                       ( (Group)object, i, new_child ) )
                            goto error;

            }
            break;

        case CLASS_FIELD:
        default:
            return object;
    }

    return object;

    error:
#if 0
        DXDelete ( (Object) );
#endif
        DXASSERT ( DXGetError() != ERROR_NONE );
        return ERROR;
}
