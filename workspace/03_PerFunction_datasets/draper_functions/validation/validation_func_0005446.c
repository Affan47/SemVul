computeKey(const Envelope& itemEnv)
{
	level=computeQuadLevel(itemEnv);
	env.init();
	computeKey(level, itemEnv);

	while (!env.contains(itemEnv)) {
		level+=1;
		computeKey(level, itemEnv);
	}
#if GEOS_DEBUG
	std::cerr<<"Key::computeKey:"<<std::endl;
	std::cerr<<" itemEnv: "<<itemEnv.toString()<<std::endl;
	std::cerr<<"  keyEnv: "<<env.toString()<<std::endl;
	std::cerr<<"  keyLvl: "<<level<<std::endl;

#endif
}
