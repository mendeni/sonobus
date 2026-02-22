#!/bin/bash

if [ -z "$1" ] ; then
   echo "Usage: $0 <version>"
   exit 1
fi

VERSION=$1

BASEAPPNAME=SonoBusMendeni

#BUILDDIR=../Builds/MacOSX/build/Release
BUILDDIR=../build/${BASEAPPNAME}_artefacts/Release
INSTBUILDDIR=../build/${BASEAPPNAME}Inst_artefacts/Release

rm -rf ${BASEAPPNAME}

mkdir -p ${BASEAPPNAME}


cp ../doc/README_MAC.txt ${BASEAPPNAME}/

cp -pLRv ${BUILDDIR}/Standalone/${BASEAPPNAME}.app  ${BASEAPPNAME}/
cp -pLRv ${BUILDDIR}/AU/${BASEAPPNAME}.component  ${BASEAPPNAME}/
cp -pLRv ${BUILDDIR}/VST3/${BASEAPPNAME}.vst3 ${BASEAPPNAME}/
cp -pLRv ${INSTBUILDDIR}/VST3/${BASEAPPNAME}Instrument.vst3 ${BASEAPPNAME}/
cp -pLRv ${BUILDDIR}/VST/${BASEAPPNAME}.vst  ${BASEAPPNAME}/
cp -pRHv ${BUILDDIR}/AAX/${BASEAPPNAME}.aaxplugin  ${BASEAPPNAME}/


#cp -pLRv ${BUILDDIR}/SonoBus.app  SonoBus/
#cp -pLRv ${BUILDDIR}/SonoBus.component  SonoBus/
#cp -pLRv ${BUILDDIR}/SonoBus.vst3 SonoBus/
#cp -pLRv ${BUILDDIR}/SonoBus.vst  SonoBus/
#cp -pRHv ${BUILDDIR}/SonoBus.aaxplugin  SonoBus/

#ln -sf /Library/Audio/Plug-Ins/Components SonoBus/
#ln -sf /Library/Audio/Plug-Ins/VST3 SonoBus/
#ln -sf /Library/Audio/Plug-Ins/VST SonoBus/
#ln -sf /Library/Application\ Support/Avid/Audio/Plug-Ins SonoBus/


# this codesigns and notarizes everything
if ! ./codesign.sh only ; then
  echo
  echo Error codesign/notarizing, stopping
  echo
  exit 1
fi

# make installer package (and sign it)

rm -f macpkg/SonoBusTemp.pkgproj

if ! ./update_package_version.py ${VERSION} macpkg/${BASEAPPNAME}.pkgproj macpkg/SonoBusTemp.pkgproj ; then
  echo
  echo Error updating package project versions
  echo
  exit 1
fi

if ! packagesbuild  macpkg/SonoBusTemp.pkgproj ; then
  echo 
  echo Error building package
  echo
  exit 1
fi

mkdir -p SonoBusPkg
rm -f SonoBusPkg/*

if ! productsign --sign ${INSTSIGNID} --timestamp  macpkg/build/${BASEAPPNAME}\ Installer.pkg SonoBusPkg/SonoBus\ Installer.pkg ; then
  echo 
  echo Error signing package
  echo
  exit 1
fi

# make dmg with package inside it

account_pwd="@keychain:Notarization-PASSWORD"
account_name="${APPLEID}" # obvsiouly you need to replace this with your developer account..
account_options="--keychain-profile SonosaurusNotarize"



if ./makepkgdmg.sh $VERSION ; then

   # ./notarizedmg.sh ${VERSION}/sonobus-${VERSION}-mac.dmg
   xcrun notarytool submit ${VERSION}/sonobusmendeni-${VERSION}-mac.dmg ${account_options} --wait
   xcrun stapler staple ${VERSION}/sonobusmendeni-${VERSION}-mac.dmg

   echo
   echo COMPLETED DMG READY === ${VERSION}/sonobusmendeni-${VERSION}-mac.dmg
   echo
   
fi
