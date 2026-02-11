tryAgain()
	{
		if(op != -1)
			return;

		QCA_logTextMessage(QString("sasl[%1]: c->tryAgain()").arg(q->objectName()), Logger::Information);
		op = OpTryAgain;
		c->tryAgain();
	}
