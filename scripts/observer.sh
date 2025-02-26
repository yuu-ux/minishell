#!/bin/bash

while : ; do
	pid=$(pgrep minishell)
	ls -la /proc/"$pid"/fd
	echo '------------------------------'
	sleep 1
done
