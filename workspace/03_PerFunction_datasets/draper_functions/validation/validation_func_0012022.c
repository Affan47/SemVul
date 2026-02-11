removeListener(const string &name)
{
    GNASH_REPORT_FUNCTION;

    boost::uint8_t *addr = _baseaddr + LC_LISTENERS_START;

    int len = 0;
	int dest= 0;
	int source =0;
    char *item = reinterpret_cast<char *>(addr);
    while (*item != 0) {
        if (name == item) {
			len =strlen(item) +8+1;

			while (*item != 0) {


				if (source!=0)
					dest  += strlen(item+source)+8+1;

				source+= strlen(item+dest)+8+1;
				strcpy(item+dest,item+source);
            }

            memset(item+dest+strlen(item+source)+8+1, 0, len);
            return true;
        }


		item += strlen(item) + 8 + 1;


	}

    return false;
}
