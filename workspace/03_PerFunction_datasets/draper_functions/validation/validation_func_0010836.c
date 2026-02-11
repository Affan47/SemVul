GetHistory (int index){
	TContext *ctx=GetCurrentContext();
	if (!ctx) return "";
	if (index<0)
		index = ctx->history.size()+index;
	if ((index<0)||(ctx->history.size()>INT_MAX)||(index>=(int)ctx->history.size())){
		return "";
	}else{
		return ctx->history[index];
	}
}
