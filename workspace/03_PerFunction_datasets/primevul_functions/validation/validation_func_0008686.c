static tjhandle _tjInitDecompress(tjinstance *this)
{
	static unsigned char buffer[1];


	this->dinfo.err=jpeg_std_error(&this->jerr.pub);
	this->jerr.pub.error_exit=my_error_exit;
	this->jerr.pub.output_message=my_output_message;
	this->jerr.emit_message=this->jerr.pub.emit_message;
	this->jerr.pub.emit_message=my_emit_message;

	if(setjmp(this->jerr.setjmp_buffer))
	{

		if(this) free(this);
		return NULL;
	}

	jpeg_create_decompress(&this->dinfo);

	jpeg_mem_src_tj(&this->dinfo, buffer, 1);

	this->init|=DECOMPRESS;
	return (tjhandle)this;
}
