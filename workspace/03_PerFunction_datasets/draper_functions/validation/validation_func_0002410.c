operator- (Vector3f const& other) const
{
	Vector3f v (m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
	return v;
}
