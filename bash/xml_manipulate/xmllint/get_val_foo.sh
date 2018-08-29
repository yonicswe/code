xmllint --stream --pattern /hello/world --debug ./foo.xml | grep -A 1 "matches pattern" | grep "#text" | sed 's/.* [0-9] //'
