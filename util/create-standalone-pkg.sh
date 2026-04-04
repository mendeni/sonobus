#!/bin/sh -x -e

APPID="com.mendeni.sonobus"
APPS="pkgroot/Applications"

cd ../build
rm -rf pkgroot

mkdir -p "$APPS"

cp -a SonoBusMendeni_artefacts/Release/Standalone/SonoBusMendeni.app "$APPS"

pkgbuild \
  --root pkgroot \
  --identifier "$APPID" \
  --version 1.7.6 \
  --install-location / \
  SonoBusMendeni.pkg
