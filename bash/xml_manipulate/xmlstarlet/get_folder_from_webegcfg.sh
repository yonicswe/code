xmlstarlet  sel -t -c "//WebEngine/Provisioning/Protocols" WebEngineCfg.xml | xmlstarlet sel -t -m "//Protocol/Folder" -v .
