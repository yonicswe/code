#!/bin/bash

LVL=${1:-3}
echo "/proc/voltaire/itarget/trace" 
cat /proc/voltaire/itarget/trace
echo "/proc/voltaire/iser/trace"
cat /proc/voltaire/iser/trace
echo "/proc/voltaire/kdapl/debug"
cat /proc/voltaire/kdapl/debug

echo "logger  $(rep_mget voltaire/modules/logger/ debug-level)" 
echo "itarget $(rep_mget voltaire/modules/itarget/ debug-level)"  
echo "scsimap $(rep_mget voltaire/modules/scsimap/ debug-level)"  
echo "iser    $(rep_mget voltaire/modules/iser_dm/ debug-level)" 
echo "kdapl   $(rep_mget voltaire/modules/kdapl/ debug-level)" 

