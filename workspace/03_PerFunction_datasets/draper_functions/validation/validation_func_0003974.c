update_targets( UniqueInputSwitch *input_switch )
{
     int            x, y, i;
     StretRegion   *region;
     UniqueContext *context;
     bool           updated[_UDCI_NUM];

     D_MAGIC_ASSERT( input_switch, UniqueInputSwitch );

     x = input_switch->x;
     y = input_switch->y;

     D_DEBUG_AT( UniQuE_InpSw, "update_targets( %d, %d )\n", x, y );

     context = input_switch->context;

     D_MAGIC_ASSERT( context, UniqueContext );

     region = stret_region_at( context->root, x, y, SRF_INPUT, SRCID_UNKNOWN );
     if (region) {
          for (i=0; i<_UDCI_NUM; i++)
               stret_region_get_input( region, i, x, y, &input_switch->targets[i].normal );
     }
     else {
          for (i=0; i<_UDCI_NUM; i++)
               input_switch->targets[i].normal = NULL;
     }

     for (i=0; i<_UDCI_NUM; i++) {
          UniqueInputTarget *target = &input_switch->targets[i];

          updated[i] = target_switch( input_switch, i,
                                      target->fixed ? : target->implicit ? : target->normal );
     }

     return updated[UDCI_POINTER];
}
