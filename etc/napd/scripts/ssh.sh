#!/bin/bash

[[ -z "$(netstat -t -n -A inet|awk -F ' ' '{print $4}'|grep ':22')" ]]
