var_get(const string& name) {
	int idx = -1;
	int submap = m_SubMap.size()-1;
	while (submap >= 0 && (idx = m_SubMap[submap]->var_get(name)) == -1) {
		submap--;
	}
	if (idx != -1) return idx;
	else return m_Map.try_get(name);
}
