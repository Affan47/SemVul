convertDateToDateTime( KJS::ExecState *exec, KJS::JSValue *value )
{
    KJS::List args;
    QDateTime returnDateTime;
    KJS::JSObject *obj = value->toObject( exec );
    if ( toQString(obj->className()) == "Date" )
    {
        int seconds = int( obj->get( exec, KJS::Identifier( "getSeconds" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        int minutes = int( obj->get( exec, KJS::Identifier( "getMinutes" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        int hours = int( obj->get( exec, KJS::Identifier( "getHours" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        int month = int( obj->get( exec, KJS::Identifier( "getMonth" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        int day = int( obj->get( exec, KJS::Identifier( "getDate" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        int year = int( obj->get( exec, KJS::Identifier( "getFullYear" ) )->toObject( exec )->call( exec, obj, args )->toInteger( exec ) );
        returnDateTime.setDate( QDate( year, month + 1, day ) );
        returnDateTime.setTime( QTime( hours, minutes, seconds ) );
    }
    else
    {

    }

    return returnDateTime;
}
