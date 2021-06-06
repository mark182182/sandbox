#!/bin/bash
#Just to make sure we don't have any artifacts... <3 .gitignore

artifacts=$(find . | grep ".exe")
num_of_artifacts=$(wc -l <<< $artifacts)
if [[ $num_of_artifacts > 0 ]]; then
  echo ""
  for artifact in $artifacts
    do
      echo "🗑️  Deleting $artifact..."
      rm -rf $artifact
    done
fi
exit 0