chewing_new()
{
	ChewingContext *ctx;

	ChewingData *internal_data = ALC( ChewingData, 1 );
	ChewingOutput *internal_output = ALC( ChewingOutput, 1 );
	ctx = ALC( ChewingContext, 1 );
	if ( ctx && internal_data && internal_output ) {
		ctx->data = internal_data;
		ctx->output = internal_output;
		ctx->cand_no = 0;


		chewing_Reset( ctx );

		return ctx;
	} else {
		return NULL;
	}
}
