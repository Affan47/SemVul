ProcessCastOrder(Unit * u,AString * o, OrdersCheck *pCheck )
{
    AString * token = o->gettoken();
    if (!token) {
        ParseError( pCheck, u, 0, "CAST: No skill given.");
        return;
    }

    int sk = ParseSkill(token);
    delete token;
    if (sk==-1) {
        ParseError( pCheck, u, 0, "CAST: Invalid skill.");
        return;
    }

    if( !( SkillDefs[sk].flags & SkillType::MAGIC )) {
        ParseError( pCheck, u, 0, "CAST: That is not a magic skill.");
        return;
    }
    if( !( SkillDefs[sk].flags & SkillType::CAST )) {
        ParseError( pCheck, u, 0, "CAST: That skill cannot be CAST.");
        return;
    }

	RangeType *rt = NULL;
    if( !pCheck ) {


        switch(sk) {
			case S_MIND_READING:
				ProcessMindReading(u,o, pCheck );
				break;
			case S_CONSTRUCT_PORTAL:
			case S_ENCHANT_SWORDS:
			case S_ENCHANT_ARMOR:
			case S_CONSTRUCT_GATE:
			case S_ENGRAVE_RUNES_OF_WARDING:
			case S_SUMMON_IMPS:
			case S_SUMMON_DEMON:
			case S_SUMMON_BALROG:
			case S_SUMMON_SKELETONS:
			case S_RAISE_UNDEAD:
			case S_SUMMON_LICH:
			case S_DRAGON_LORE:
			case S_WOLF_LORE:
			case S_EARTH_LORE:
			case S_CREATE_RING_OF_INVISIBILITY:
			case S_CREATE_CLOAK_OF_INVULNERABILITY:
			case S_CREATE_STAFF_OF_FIRE:
			case S_CREATE_STAFF_OF_LIGHTNING:
			case S_CREATE_AMULET_OF_TRUE_SEEING:
			case S_CREATE_AMULET_OF_PROTECTION:
			case S_CREATE_RUNESWORD:
			case S_CREATE_SHIELDSTONE:
			case S_CREATE_MAGIC_CARPET:
			case S_CREATE_FOOD:
				ProcessGenericSpell(u,sk, pCheck );
				break;
			case S_CLEAR_SKIES:
				rt = FindRange(SkillDefs[sk].range);
				if (rt == NULL)
					ProcessGenericSpell(u, sk, pCheck);
				else
					ProcessRegionSpell(u, o, sk, pCheck);
				break;
			case S_FARSIGHT:
			case S_TELEPORTATION:
			case S_WEATHER_LORE:
				ProcessRegionSpell(u, o, sk, pCheck);
				break;
			case S_BIRD_LORE:
				ProcessBirdLore(u,o, pCheck );
				break;
			case S_INVISIBILITY:
				ProcessInvisibility(u,o, pCheck );
				break;
			case S_GATE_LORE:
				ProcessCastGateLore(u,o, pCheck );
				break;
			case S_PORTAL_LORE:
				ProcessCastPortalLore(u,o, pCheck );
				break;
			case S_CREATE_PHANTASMAL_BEASTS:
				ProcessPhanBeasts(u,o, pCheck );
				break;
			case S_CREATE_PHANTASMAL_UNDEAD:
				ProcessPhanUndead(u,o, pCheck );
				break;
			case S_CREATE_PHANTASMAL_DEMONS:
				ProcessPhanDemons(u,o, pCheck );
				break;
		}
	}
}
