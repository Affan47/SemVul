LocalDeclStatement()
	{
		SQObject varname;
		do {
			Lex(); varname = Expect(TK_IDENTIFIER);
			if(_token == _SC('=')) {
				Lex(); Expression();
				SQInteger src = _fs->PopTarget();
				SQInteger dest = _fs->PushTarget();
				if(dest != src) _fs->AddInstruction(_OP_MOVE, dest, src);
			}
			else{
				_fs->AddInstruction(_OP_LOADNULLS, _fs->PushTarget(),1);
			}
			_fs->PopTarget();
			_fs->PushLocalVariable(varname);

		} while(_token == _SC(','));
	}
