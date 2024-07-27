#!/bin/bash

# Read parent pid, child pid
while [ "$#" -gt 0 ]; do
  case "$1" in
    --parent)
      parent="$2"
      shift 2
      ;;
    --child)
      child="$2"
      shift 2
      ;;
    *)
      echo "Unknown parameter passed: $1"
      exit 1
      ;;
  esac
done

# Check if parent or child is empty
if [ -z "$parent" ] || [ -z "$child" ]; then
  echo "Usage: $0 --parent PARENT_PID --child CHILD_PID [--path]"
  exit 1
fi

########
# TODO #
########


ancestor() {
  local child_pid="$1"
  local target_pid="$2"
  
 
  local ppid="$(ps -o ppid= -p "$child_pid" | tr -d ' ')"
 
  if [ "$ppid" -eq 1 ]; then  #root
    echo "No" 
  elif [ "$ppid" -eq "$target_pid" ]; then
    echo "Yes"
  else
    ancestor "$ppid" "$target_pid" 
  fi
}

result=$(ancestor "$child" "$parent")

if [ "$result" == "Yes" ]; then
  echo "Yes"
else
  echo "No"
fi





# The code below is only for demonstration purposes, please remove it before submitting.
#echo "parent pid: $parent, child pid: $child"
