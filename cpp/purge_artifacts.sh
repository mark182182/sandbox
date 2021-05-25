#!/bin/bash
#Just to make sure we don't have any artifacts... <3 .gitignore

artifacts=$(find . | grep ".exe")
num_of_artifacts=$(wc -l <<< $artifacts)
if [[ $num_of_artifacts > 0 ]]; then
  echo "Purging..."
  for artifact in $artifacts
    do
      rm -rf $artifact
    done
fi
exit 0