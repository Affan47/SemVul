trade_rating(int nationRecno)
{


	int tradeRating1 = 100 * (int) total_year_trade(nationRecno) / 5000;

	int tradeRating2 = 50 * (int) nation_array[nationRecno]->get_relation(nation_recno)->last_year_import[IMPORT_TOTAL] / (int) (last_year_income+1) +
							 50 * (int) get_relation(nationRecno)->last_year_import[IMPORT_TOTAL] / (int) (last_year_expense+1);

	return MAX(tradeRating1, tradeRating2);
}
