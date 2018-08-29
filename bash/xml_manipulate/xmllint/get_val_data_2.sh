# xmllint --xpath '/project/name/text()' data_2.xml | xargs -i echo -n "{}"
xmllint --xpath '/project/name/text()' data_2.xml
