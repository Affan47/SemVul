ipcp_vr_lattice::set_to_bottom ()
{
  if (m_vr.varying_p ())
    return false;


  m_vr.set_varying (integer_type_node);
  return true;
}
