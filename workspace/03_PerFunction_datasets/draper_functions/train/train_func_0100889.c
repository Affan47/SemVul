displayPrimSkill()
{
	_primSkill = new AskCombo( tr( "Primary skill: " ), this );
	_primSkill->insertItem( tr( "Attack" ) );
	_primSkill->insertItem( tr( "Defense" ) );
	_primSkill->insertItem( tr( "Power" ) );
	_primSkill->insertItem( tr( "Knowledge" ) );
	_primSkill->insertItem( tr( "Morale" ) );
	_primSkill->insertItem( tr( "Luck" ) );
	_primSkill->insertItem( tr( "Charisma" ) );
	_primSkill->setCurrentItem( _bonus->getParam( 0 ) );

	_value = new AskInt( tr( "Add value: " ), this );
	_value->setValue( _bonus->getParam( 1 ) );

	QVBoxLayout * layout = new QVBoxLayout( this );
	layout->setMargin( 5 );
	layout->setSpacing( 5 );
	layout->addWidget( _primSkill );
	layout->addWidget( _value );
	layout->addStretch( 1 );
	layout->activate();
}
