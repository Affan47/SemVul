lex( void *_yylval )
{
    YYSTYPE *yylval = (YYSTYPE *)_yylval;
    int token = lex();
    int length;
    unsigned short *t = text( &length );

#ifdef TOKEN_DEBUG
    qDebug("CSSTokenizer: got token %d: '%s'", token, token == END ? "" : QString( (QChar *)t, length ).toLatin1().constData() );
#endif
    switch( token ) {
    case '{':
        block_nesting++;
        break;
    case '}':
        if ( block_nesting )
            block_nesting--;
        break;
    case END:
        if ( block_nesting ) {
            block_nesting--;
            return '}';
        }
        break;
    case S:
    case SGML_CD:
    case INCLUDES:
    case DASHMATCH:
        break;

    case URI:
    case STRING:
    case IDENT:
    case NTH:
    case HASH:
    case HEXCOLOR:
    case DIMEN:
    case UNICODERANGE:
    case NOTFUNCTION:
    case FUNCTION:
        yylval->string.string = t;
        yylval->string.length = length;
        break;

    case IMPORT_SYM:
    case PAGE_SYM:
    case MEDIA_SYM:
    case FONT_FACE_SYM:
    case CHARSET_SYM:
    case NAMESPACE_SYM:

    case IMPORTANT_SYM:
        break;

    case QEMS:
        length--;
    case GRADS:
    case DPCM:
        length--;
    case DEGS:
    case RADS:
    case KHERZ:
    case DPI:
        length--;
    case MSECS:
    case HERZ:
    case EMS:
    case EXS:
    case PXS:
    case CMS:
    case MMS:
    case INS:
    case PTS:
    case PCS:
        length--;
    case SECS:
    case PERCENTAGE:
        length--;
    case FLOAT:
    case INTEGER:
        yylval->val = qMin(QString((QChar *)t, length).toDouble(), dIntMax);

        break;

    default:
        break;
    }

    return token;
}
