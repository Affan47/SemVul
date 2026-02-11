RemoveDefaultRoute(BufferedTransformation &destination)
{
	for (DefaultRouteList::iterator it = m_defaultRoutes.begin(); it != m_defaultRoutes.end(); ++it)
		if (it->first == &destination && !it->second.get())
		{
			m_defaultRoutes.erase(it);
			break;
		}
}
