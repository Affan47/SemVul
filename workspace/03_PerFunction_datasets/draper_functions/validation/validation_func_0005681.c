setTemplateIdentification(const OFString &templateIdentifier,
                                                      const OFString &mappingResource)
{
    OFCondition result = EC_IllegalCall;
    if (TreeNode != NULL)
        result = TreeNode->setTemplateIdentification(templateIdentifier, mappingResource);
    return result;
}
