knights_who_won (Pos *pos, Player player, char **commp)
{
	int i=0, j=0, k;
	float eval;
	ResultType result = knights_eval_real (pos, player, &eval, TRUE);
	if (result == RESULT_NOTYET)
		;
	else if (result == RESULT_TIE) *commp = "Draw";
	else if (result == RESULT_WHITE) *commp = "White won";
	else if (result == RESULT_BLACK) *commp = "Black won";
	return result;
}
