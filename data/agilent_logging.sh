#!/bin/bash
LOGFILE=disch_log.txt
LOG_INTERVAL=1			# duration between samples
#LOG_TIME=100				#-1 - sets infinite time

#LOG_TIME=$(LOG_TIME)+("date +%s")
TIME=`date +%s`
echo "log started at" $TIME >> $LOGFILE


#no error checking atm, feel free to add
#u1272a.pl doesn't work with multiple multimeters, but should be possible to modify so that it does

#log forever
while [ 1 ]
do
	VOLTAGE=`./u1272a.pl | grep reading: | cut -f2 -d" "`
	TIME=`date +%s`		# add timestamp
	echo $VOLTAGE $TIME >> $LOGFILE
	echo $VOLTAGE $TIME
	sleep $LOG_INTERVAL
done
