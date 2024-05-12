#!/bin/bash
source ~/.bashrc

pathToScript=$1

if [[ -z $pathToScript ]]; then
  echo "Usage: start.sh [pathToScript]"
  exit 1;
fi

conda activate tfVenv
statusCode=$?

if [[ $statusCode != 0 ]]; then
  conda create -n tfVenv python=3.9 anaconda::tensorflow tensorflow-probability conda-forge::tensorflow-datasets==4.2.0 gym conda-forge::gym-toy_text anaconda::pillow pandas matplotlib numpy --yes

  statusCode=$?

  conda activate tfVenv
fi


if [[ $statusCode == 0 ]]; then
  python $pathToScript
fi