gxmessage -center -buttons "yoni":1,"dvori":2 -title "yoni is great" "linux is wonderfull"
answer=$?
case "$answer" in 
1) gxmessage -center "you chose yoni"
;;
2) gxmessage -center "you chose dvori"
;;
esac

