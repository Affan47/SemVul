commit()
{
    switch( d->type ) {
        case Private::ActionType: {
            d->action->setText( d->textedit->text() );
            d->action->setDescription( d->commentedit->text() );
            d->action->setIconName( d->iconedit->text() );
            d->action->setInterpreter( d->interpreteredit->currentText() );
            d->action->setFile( d->fileedit->url().path() );

        } break;
        case Private::CollectionType: {
            d->collection->setText( d->textedit->text() );
            d->collection->setDescription( d->commentedit->text() );
            d->collection->setIconName( d->iconedit->text() );

        } break;
        default: break;
    }
}
