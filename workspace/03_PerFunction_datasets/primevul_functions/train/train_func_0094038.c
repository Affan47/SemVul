QPDFWriter::adjustAESStreamLength(size_t& length)
{
    if (this->encrypted && (! this->cur_data_key.empty()) &&
	this->encrypt_use_aes)
    {


	length += 32 - (length & 0xf);
    }
}
