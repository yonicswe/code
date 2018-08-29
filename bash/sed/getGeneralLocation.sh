#!/bin/bash

# print only text between to patterns 

sed -n -e '/^GENERAL_LOCATION/,/^\[WebEngine\]/ {   /^\[WebEngine\]/d; p  }' $1


# the following input
# ================================
# Web Engine Output Stream
# ------------------------
# GENERAL_LOCATION
# Out Obj:
# 4444444 : 1.28
# 
# Out Obj:
# 4444444 : 1.28
# 
# Out Obj:
# 4444444 : 103.84
# 
# 
# [WebEngine] ./out/DebugReceiver.cpp(14) ::receive 
# Web Engine Output Stream
# [WebEngine] ./ruleEngine/Rule.cpp(29) ::eval MATCH maptiles.accuweather.com
# /accuwxandroidv3/tiles/worldSat/570d1bfcb/0155/7/100_62.png

# would create the following output
# ==================================
# GENERAL_LOCATION
# Out Obj:
# 4444444 : 1.28
# 
# Out Obj:
# 4444444 : 1.28
# 
# Out Obj:
# 4444444 : 103.84
# 
