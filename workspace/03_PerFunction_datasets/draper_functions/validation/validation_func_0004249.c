submitFromKeyboard()
{


    unsigned int inputtext = 0;
    for (QListIterator<HTMLGenericFormElementImpl*> it(formElements); it.hasNext();) {
        HTMLGenericFormElementImpl* const cur = it.next();
        if (cur->id() == ID_BUTTON) {
            HTMLButtonElementImpl* const current = static_cast<HTMLButtonElementImpl *>(cur);
            if (current->buttonType() == HTMLButtonElementImpl::SUBMIT && !current->disabled()) {
                current->click();
                return;
            }
        } else if (cur->id() == ID_INPUT) {
            HTMLInputElementImpl* const current = static_cast<HTMLInputElementImpl *>(cur);
            switch(current->inputType())  {
            case HTMLInputElementImpl::SUBMIT:
            case HTMLInputElementImpl::IMAGE:
		if(!current->disabled()) {
			current->click();
			return;
		}
		break;
            case HTMLInputElementImpl::TEXT:
            case HTMLInputElementImpl::PASSWORD:
                ++inputtext;
            default:
                break;
            }
        }
    }

    if (inputtext <= 1)
        prepareSubmit();
}
