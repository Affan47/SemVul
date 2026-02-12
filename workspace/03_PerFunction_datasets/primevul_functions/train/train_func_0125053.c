PHPAPI zend_string *php_escape_shell_arg(char *str)
{
	int x, y = 0, l = strlen(str);
	zend_string *cmd;
	size_t estimate = (4 * l) + 3;

	TSRMLS_FETCH();

	cmd = STR_ALLOC(4 * l + 2, 0);

#ifdef PHP_WIN32
	cmd->val[y++] = '"';
#else
	cmd->val[y++] = '\'';
#endif

	for (x = 0; x < l; x++) {
		int mb_len = php_mblen(str + x, (l - x));


		if (mb_len < 0) {
			continue;
		} else if (mb_len > 1) {
			memcpy(cmd->val + y, str + x, mb_len);
			y += mb_len;
			x += mb_len - 1;
			continue;
		}

		switch (str[x]) {
#ifdef PHP_WIN32
		case '"':
		case '%':
			cmd->val[y++] = ' ';
			break;
#else
		case '\'':
			cmd->val[y++] = '\'';
			cmd->val[y++] = '\\';
			cmd->val[y++] = '\'';
#endif

		default:
			cmd->val[y++] = str[x];
		}
	}
#ifdef PHP_WIN32
	cmd->val[y++] = '"';
#else
	cmd->val[y++] = '\'';
#endif
	cmd->val[y] = '\0';

	if ((estimate - y) > 4096) {


		cmd = STR_REALLOC(cmd, y, 0);
	}
	cmd->len = y;
	return cmd;
}
