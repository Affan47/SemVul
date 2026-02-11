get_width_height(double& width, double& height) const
{
  if(m_child)
    m_child->get_width_height(width, height);
  else
  {
    width = m_width;
    height = m_height;
  }


  if(width == -1)
    width = 100;

  if(height == -1)
    height = 100;
}
