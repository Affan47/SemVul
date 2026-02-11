save(ofstream & fp) const{
		saveValue(fp, npr_type);
		saveValue(fp, n);
		saveValue(fp, b);
		saveValue(fp, bits_b);
		saveValue(fp, l);
		saveValue(fp, level_size, l);
		for(size_t i=0; i<l; i++)
			saveValue(fp, min_level[i], level_size[i]);
		for(size_t i=0; i<l; i++)
			saveValue(fp, min_pos[i], (level_size[i]*bits_b+W-1)/W);
	}
