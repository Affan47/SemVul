input_device_callback( DFBInputDeviceID           id,
                       DFBInputDeviceDescription  desc,
                       void                      *arg )
{
     int i;


     printf( "Input (%02x) %-30s", id, desc.name );

     switch (id) {
          case DIDID_JOYSTICK:
               printf( "  (primary joystick)" );
               break;
          case DIDID_KEYBOARD:
               printf( "  (primary keyboard)" );
               break;
          case DIDID_MOUSE:
               printf( "  (primary mouse)" );
               break;
          case DIDID_REMOTE:
               printf( "  (primary remote control)" );
               break;
          default:
               break;
     }

     printf( "\n" );


     printf( "   Type: " );

     for (i=0; input_types[i].type; i++) {
          if (desc.type & input_types[i].type)
               printf( "%s ", input_types[i].name );
     }

     printf( "\n" );


     printf( "   Caps: " );

     for (i=0; input_caps[i].capability; i++) {
          if (desc.caps & input_caps[i].capability)
               printf( "%s ", input_caps[i].name );
     }

     printf( "\n" );


     if (desc.caps & DICAPS_KEYS)
          printf( "   Min. Keycode: %d\n", desc.min_keycode );
     if (desc.caps & DICAPS_KEYS)
          printf( "   Max. Keycode: %d\n", desc.max_keycode );
     if (desc.caps & DICAPS_AXES)
          printf( "   Max. Axis: %d\n", desc.max_axis );
     if (desc.caps & DICAPS_BUTTONS)
          printf( "   Max. Button: %d\n", desc.max_button );


     printf( "\n" );

     return DFB_OK;
}
