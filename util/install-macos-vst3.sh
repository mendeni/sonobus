#!/bin/sh

TARGET='/Library/Audio/Plug-Ins/VST3/SonoBusMendeni'

if [ ! -d $TARGET ]; then
  mkdir $TARGET || exit 1
fi

if [ ! -d 'VST3' ]; then
  echo "VST3 folder not found, exiting"
  exit 1
fi

cd VST3 && cp -a * $TARGET

codesign --force --deep --sign - $TARGET/SonoBusMendeni.vst3/Contents/MacOS/SonoBusMendeni

spctl --master-disable
spctl --status

echo "Don't forget to re-enable afer install"
echo "spctl --master-enable"
