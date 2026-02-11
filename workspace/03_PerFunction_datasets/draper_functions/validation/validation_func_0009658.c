icalcomponent_isa (const icalcomponent* component)
{
   icalerror_check_arg_rx( (component!=0), "component", ICAL_NO_COMPONENT);

   if(component != 0)
   {
       return component->kind;
   }

   return ICAL_NO_COMPONENT;
}
