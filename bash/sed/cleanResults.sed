#!/bin/sed -i
#     command = "find " + path + " -type f | xargs sed -i 's/^time:.*,/time: 000,/g'"
#     command = "find " + path + " -type f | xargs -I {} sed -i 's/" + key + ".*/" + key + "/g' {}"
#     command = "find " + path + " -type f | xargs -I {} sed -i 's/\(\[WebEngine\][^(]*\)([^)]*)/\[WebEngine\] /g' {}" 
s/^time:.*,/time: 000,/g
s/MAIL_ATTACHMENT_FILE_ID.*/" + key + "/g
s/\(\[WebEngine\][^(]*\)([^)]*)/\[WebEngine\] /g
