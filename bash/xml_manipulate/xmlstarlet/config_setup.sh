#!/bin/bash

# 
#  usage exmples   
# ---8<----------------
#	  get_wbe_path HTTP
#	  get_wbe_path NNTP
#	  
#	  set_mdadaptor yoni
#	  set_wbe_path /etc/nice/ips/wbein/ HTTP http
#  	  
#     set_ss_adaptor sandvine	  
# ---8<----------------
# 

AUTOREGRESSION_PATH=/home/kuser/autoRegression
source ${AUTOREGRESSION_PATH}/scripts/global_vars.sh

web_engine_config_file=${CONFIG_PATH}/WebEngineCfg.xml
ips_analyzer_config_file=${CONFIG_PATH}/IPS_Analyzer.xml
app_config_file=${CONFIG_PATH}/AppConfig.xml

set_mdadaptor () 
{
	local adaptor=$1;

 	xmlstarlet ed -P -L -u "//IPS/MDAdaptorMng/MDAdaptorDLLPath" -v ${adaptor} ${ips_analyzer_config_file};
}

get_mdadaptor () 
{
 	xmlstarlet sel -B -t -v "//IPS/MDAdaptorMng/MDAdaptorDLLPath" ${ips_analyzer_config_file} | sed -e 's/\ //g' -e 's/\t//g'; 
}


set_wbe_path () 
{
	local root=$1;
	local name=$2;
	local folder=$3; 

	# set root
	xmlstarlet ed -P -L -u "//WebEngine/Provisioning/Protocols/Root" -v ${root} ${web_engine_config_file};

			
	xmlstarlet ed -P -L -u "//WebEngine/Provisioning/Protocols/Protocol[Name='${name}']/Folder" -v ${folder} ${web_engine_config_file};
} 

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

get_ss_adaptor () 
{
 	xmlstarlet sel -B -t -v "//gt:AppConfig/gt:streamSource/gt:streamSourceAdaptor" ${app_config_file} | sed -e 's/\ //g' -e 's/\t//g'; 
}

set_ss_adaptor () 
{
	local adaptor=${1};

 	xmlstarlet ed -P -L -u "//gt:AppConfig/gt:streamSource/gt:streamSourceAdaptor" -v ${adaptor} ${app_config_file}
}

set_dfm_exporter () 
{
	local enable_disable=${1};

 	xmlstarlet ed -P -L -u "//gt:AppConfig/gt:streamSource/gt:streamSourceAdaptor" -v ${enable_disable} ${web_engine_config_file} 
}

get_dfm_exporter () 
{
 	xmlstarlet sel -B -t -v "//gt:AppConfig/gt:streamSource/gt:streamSourceAdaptor" ${web_engine_config_file} | sed -e 's/\ //g' -e 's/\t//g'; 
}

#=================================================================================

setup_config_for_we () 
{
	set_mdadaptor libMDAdaptorDFM.so
}

get_dfm_exporter
