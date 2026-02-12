combine_access(limited_rights_t *target,
               const limited_rights_t *rights)
{


  if (target->access.sequence_number < rights->access.sequence_number)
    target->access = rights->access;
}
