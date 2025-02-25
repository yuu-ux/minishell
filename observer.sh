#!/bin/bash

while : ; do
	pid=$(ps aux | grep minishell | grep -v grep | awk '{ print $2 }')
	ls -la /proc/"$pid"/fd
	echo '------------------------------'
	sleep 1
done
