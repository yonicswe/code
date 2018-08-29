#!/bin/bash

set_wbe_path () 
{
	local root=$1;
	local name=$2;
	local folder=$3; 

	# set root
	xmlstarlet ed -L -u "//WebEngine/Provisioning/Protocols/Root" -v ${root} WebEngineCfg.xml

			
	xmlstarlet ed -L -u "//WebEngine/Provisioning/Protocols/Protocol[Name='${name}']/Folder" -v ${folder} WebEngineCfg.xml
}


set_wbe_path /etc/nice/ips/wbein/ HTTP http
