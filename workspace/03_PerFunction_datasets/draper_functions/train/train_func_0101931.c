addInternalAI()
{

 TRACE("ServerInterface::addInternalAI");

	QStringList arglist;
	AttalSocket * socket = new AttalSocket;
	Analyst * ai = new Analyst( socket );
	socket->connectToHost( "localhost", PORT.toInt() );
	_aiList.append( ai );
	ai->start();
}
