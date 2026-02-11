update_ai_firm_array(int firmId, int actionType, int actionRecno, int& arrayCount)
{
	short* rc;

	switch(firmId)
	{
		case FIRM_BASE:
			rc = update_ai_array(ai_base_count, ai_base_size, &ai_base_array,
					 AI_BASE_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_base_count;
			break;

		case FIRM_CAMP:
			rc = update_ai_array(ai_camp_count, ai_camp_size, &ai_camp_array,
					 AI_CAMP_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_camp_count;
			break;

		case FIRM_FACTORY:
			rc = update_ai_array(ai_factory_count, ai_factory_size, &ai_factory_array,
					 AI_FACTORY_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_factory_count;
			break;

		case FIRM_MARKET:
			rc = update_ai_array(ai_market_count, ai_market_size, &ai_market_array,
					 AI_MARKET_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_market_count;
			break;

		case FIRM_INN:
			rc = update_ai_array(ai_inn_count, ai_inn_size, &ai_inn_array,
					 AI_INN_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_inn_count;
			break;

		case FIRM_MINE:
			rc = update_ai_array(ai_mine_count, ai_mine_size, &ai_mine_array,
				  AI_MINE_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_mine_count;
			break;

		case FIRM_RESEARCH:
			rc = update_ai_array(ai_research_count, ai_research_size, &ai_research_array,
					 AI_RESEARCH_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_research_count;
			break;

		case FIRM_WAR_FACTORY:
			rc = update_ai_array(ai_war_count, ai_war_size, &ai_war_array,
					 AI_WAR_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_war_count;
			break;

		case FIRM_HARBOR:
			rc = update_ai_array(ai_harbor_count, ai_harbor_size, &ai_harbor_array,
					 AI_HARBOR_INC_SIZE, actionType, actionRecno);
			arrayCount = ai_harbor_count;
			break;

		default:
			err_here();
			return 0;
	}

	return rc;
}
