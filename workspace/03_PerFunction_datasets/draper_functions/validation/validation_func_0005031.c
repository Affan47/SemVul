CompileTypemask(SQIntVec &res,const SQChar *typemask)
{
	SQInteger i = 0;

	SQInteger mask = 0;
	while(typemask[i] != 0) {

		switch(typemask[i]){
				case 'o': mask |= _RT_NULL; break;
				case 'i': mask |= _RT_INTEGER; break;
				case 'f': mask |= _RT_FLOAT; break;
				case 'n': mask |= (_RT_FLOAT | _RT_INTEGER); break;
				case 's': mask |= _RT_STRING; break;
				case 't': mask |= _RT_TABLE; break;
				case 'a': mask |= _RT_ARRAY; break;
				case 'u': mask |= _RT_USERDATA; break;
				case 'c': mask |= (_RT_CLOSURE | _RT_NATIVECLOSURE); break;
				case 'b': mask |= _RT_BOOL; break;
				case 'g': mask |= _RT_GENERATOR; break;
				case 'p': mask |= _RT_USERPOINTER; break;
				case 'v': mask |= _RT_THREAD; break;
				case 'x': mask |= _RT_INSTANCE; break;
				case 'y': mask |= _RT_CLASS; break;
				case 'r': mask |= _RT_WEAKREF; break;
				case '.': mask = -1; res.push_back(mask); i++; mask = 0; continue;
				case ' ': i++; continue;
				default:
					return false;
		}
		i++;
		if(typemask[i] == '|') {
			i++;
			if(typemask[i] == 0)
				return false;
			continue;
		}
		res.push_back(mask);
		mask = 0;

	}
	return true;
}
