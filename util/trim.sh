#!/bin/sh

cd ~/Music/SonoBus

for f in *.rtms
do
  if [ -e "$f" ]; then
    cat "$f" | trim.sox.pl ~/Music/SonoBus
    mv "$f" "$f.trimmed"
  fi
done
