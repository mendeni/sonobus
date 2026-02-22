#!/bin/bash

BASEAPPNAME=SonoBusMendeni


# codesign them with developer ID cert

DEVIDSHA="53B30F159F221174875C0241213FE6B7B3CFE483"

POPTS="--strict  --force --options=runtime --sign ${DEVIDSHA} --timestamp"
AOPTS="--strict  --force --options=runtime --sign ${DEVIDSHA} --timestamp"

codesign ${AOPTS} --entitlements SonoBus.entitlements ${BASEAPPNAME}/${BASEAPPNAME}.app
codesign ${POPTS} --entitlements SonoBus.entitlements  ${BASEAPPNAME}/${BASEAPPNAME}.component
codesign ${POPTS} --entitlements SonoBus.entitlements ${BASEAPPNAME}/${BASEAPPNAME}.vst3
codesign ${POPTS} --entitlements SonoBus.entitlements ${BASEAPPNAME}/${BASEAPPNAME}Instrument.vst3
codesign ${POPTS} --entitlements SonoBus.entitlements  ${BASEAPPNAME}/${BASEAPPNAME}.vst

# AAX is special
if [ -n "${AAXSIGNCMD}" ]; then
 echo "Signing AAX plugin"
 ${AAXSIGNCMD}  --in ${BASEAPPNAME}/${BASEAPPNAME}.aaxplugin --out ${BASEAPPNAME}/${BASEAPPNAME}.aaxplugin
fi


if [ "x$1" = "xonly" ] ; then
  echo Code-signing only
  exit 0
fi

# don't notarize here ever
exit 0

mkdir -p tmp

# notarize them in parallel
./notarize-app.sh --submit=tmp/sbapp.uuid  SonoBus/SonoBus.app
./notarize-app.sh --submit=tmp/sbau.uuid SonoBus/SonoBus.component
./notarize-app.sh --submit=tmp/sbvst3.uuid SonoBus/SonoBus.vst3
./notarize-app.sh --submit=tmp/sbinstvst3.uuid SonoBus/SonoBusInstrument.vst3
./notarize-app.sh --submit=tmp/sbvst2.uuid SonoBus/SonoBus.vst 

if ! ./notarize-app.sh --resume=tmp/sbapp.uuid SonoBus/SonoBus.app ; then
  echo Notarization App failed
  exit 2
fi

if ! ./notarize-app.sh --resume=tmp/sbau.uuid SonoBus/SonoBus.component ; then
  echo Notarization AU failed
  exit 2
fi

if ! ./notarize-app.sh --resume=tmp/sbvst3.uuid SonoBus/SonoBus.vst3 ; then
  echo Notarization VST3 failed
  exit 2
fi

if ! ./notarize-app.sh --resume=tmp/sbinstvst3.uuid SonoBus/SonoBusInstrument.vst3 ; then
  echo Notarization Inst VST3 failed
  exit 2
fi
  
if ! ./notarize-app.sh --resume=tmp/sbvst2.uuid SonoBus/SonoBus.vst ; then
  echo Notarization VST2 failed
  exit 2
fi

#if ! ./notarize-app.sh SonoBus/SonoBus.aaxplugin ; then
#  echo Notarization AAX failed
#  exit 2
#fi





