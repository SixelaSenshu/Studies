#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <init|service> <deleg|resp>"
    exit 1
fi

mode=$1
type=$2


case $mode in
    "init")
	case $type in
	    "deleg")
	  	echo "run init delegatiion"
		cd ./Services/Delegation/
		python3 initialisation.py
		cd ../../
		;;
	    "resp")
	   	echo "run init resp_part"
	   	cd ./Services/Resp_Part/
	      	python3 initialisation.py
	      	cd ../../
		;;
	    *)
		exit 1
		;;
	esac
        ;;
    "service")
        case $type in
	    "deleg")
	    	echo "run service delegatiion"
	    	cd ./Services/Delegation/
		python3 service.py
		cd ../../
		;;
	    "resp")
	    	echo "run service resp_part"
	    	cd ./Services/Resp_Part/
	      	python3 service.py
	      	cd ../../
		;;
	    *)
		exit 1
		;;
	esac
        ;;
    *)
        exit 1
        ;;
esac



