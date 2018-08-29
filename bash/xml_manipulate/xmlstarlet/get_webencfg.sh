
echo "============== xmllint ================="
xmllint --debug --xpath '/WebEngine/Provisioning/Protocols/Protocol/Folder/text()' WebEngineCfg.xml

echo
echo "============== xmlstarlet ================="
xmlstarlet sel -t -v  '/WebEngine/Provisioning/Protocols/Protocol/Folder' WebEngineCfg.xml
