#!/bin/bash					

get_wbe_all_paths () 
{
	declare -a folders;
	declare -a names;
	local folder;
	local root;
	local index=0;

	root=$(xmlstarlet sel -B -t -v "//WebEngine/Provisioning/Protocols/Root" WebEngineCfg.xml | sed 's/\ //g');

	names=( $(xmlstarlet sel  -t -m //WebEngine/Provisioning/Protocols/Protocol -v Name -o " "  WebEngineCfg.xml ) );		
	folders=( $(xmlstarlet sel  -t -m //WebEngine/Provisioning/Protocols/Protocol -v Folder -o " "  WebEngineCfg.xml ) );		

	for folder in ${folders[*]} ; do 
		echo "${names[$index]}  ${root}${folder}";
		((index++));			
	done					
}

get_wbe_path () 
{ 
	name=${1};
	get_wbe_all_paths | awk "/${name}/{print $2}";
}

get_wbe_path HTTP
get_wbe_path NNTP
