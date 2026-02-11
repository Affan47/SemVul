findMultiAddressObjectsUsedInRules(FWObject *top)
{
    if (top->getInt(".recursion_breaker") == infinite_recursion_breaker)
        return;
    top->setInt(".recursion_breaker", infinite_recursion_breaker);

    for (FWObject::iterator i=top->begin(); i!=top->end(); ++i)
    {
        FWObject *obj = *i;
        PolicyRule *rule = PolicyRule::cast(obj);
        if (rule && rule->getAction() == PolicyRule::Branch)
        {
            RuleSet *branch_ruleset = rule->getBranch();
            if (branch_ruleset)
                findMultiAddressObjectsUsedInRules(branch_ruleset);
        }

        FWReference *ref = FWReference::cast(obj);
        if (ref == NULL)
            findMultiAddressObjectsUsedInRules(obj);
        else
        {
            FWObject *obj_ptr = FWReference::getObject(obj);
            if (obj_ptr->getInt(".loaded") == infinite_recursion_breaker)
                continue;
            obj_ptr->setInt(".loaded", infinite_recursion_breaker);

            try
            {
                convertObject(obj_ptr);
            } catch (FWException &ex) {
                abort(ex.toString());
            }


            if (Group::cast(obj_ptr))
                findMultiAddressObjectsUsedInRules(obj_ptr);
        }
    }
}
