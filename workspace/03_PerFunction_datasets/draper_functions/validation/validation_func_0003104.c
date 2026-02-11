abs_event( const struct input_event *levt,
           DFBInputEvent            *devt )
{
     switch (levt->code) {
          case ABS_X:
               devt->axis = DIAI_X;
               break;

          case ABS_Y:
               devt->axis = DIAI_Y;
               break;

          case ABS_Z:
          case ABS_WHEEL:
               devt->axis = DIAI_Z;
               break;

          default:
               if (levt->code >= ABS_PRESSURE || levt->code > DIAI_LAST)
                    return false;
               devt->axis = levt->code;
     }

     devt->type    = DIET_AXISMOTION;
     devt->flags  |= DIEF_AXISABS;
     devt->axisabs = levt->value;

     return true;
}
