#!/bin/bash

while : ; do
	ps axjf | grep minishell | grep -v grep
	sleep 2
done
