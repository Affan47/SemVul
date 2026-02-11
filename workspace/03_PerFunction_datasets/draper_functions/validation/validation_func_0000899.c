update_monsters(bool full)
{
	int i;


	for (i = 1; i < cave_monster_max(cave); i++)
	{
		monster_type *m_ptr = cave_monster(cave, i);


		if (!m_ptr->r_idx) continue;


		update_mon(i, full);
	}
}
