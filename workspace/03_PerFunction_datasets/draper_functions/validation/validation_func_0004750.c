tfgetc(fp)
	TFILE *fp;
{
	int c, f, m, look = 0;

	if (! _ioexit) {
		if (atkexit (tfcloseall, (char *) 0) != 0)
			return (EOF);
		_ioexit = 1;
	}

	f = (fp->_flag &= ~_TIORW);
	if(!(f & _TIOREAD) || (f & (_TIOERR | _TIOEOF)))
		return(EOF);
	if(fp->_base == NULL)
		_getbuf(fp);
_fgetc1:
	if(--(fp->_cnt) < 0) {
		m = (int) lam_iomap_read(fp->_flag,
					fp->_file,
					(char *) fp->_base,
					(long) fp->_bsiz);
		if(m <= 0) {
			fp->_flag |= ((m == 0) ? _TIOEOF : _TIOERR);
			c = EOF;
			goto _fgetc2;
		}
		fp->_cnt = (m - 1);
		fp->_ptr = fp->_base;
	}
	c = *(fp->_ptr)++;
_fgetc2:
	if (!(f & _TIOBIN)) {
		if (look) {
			if(c != '\n') {
				if(c == EOF) {
					fp->_flag &= ~(_TIOERR | _TIOEOF);
				} else {
					*--(fp->_ptr) = c;
					++(fp->_cnt);
				}
				c = '\r';
			}
		} else if(c == '\r') {
			if(f & _TIODEV)
				c = '\n';
			else {
				look = 1;
				goto _fgetc1;
			}
		} else if(c == 0x00) {
			goto _fgetc1;
		} else if(c == 0x1A) {
			fp->_flag |= _TIOEOF;
			c = EOF;
		}
	}
	return(c);
}
