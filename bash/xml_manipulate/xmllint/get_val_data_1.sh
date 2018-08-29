xmllint --xpath '/project/version/text()' data_1.xml | xargs -i echo -n "{}"
