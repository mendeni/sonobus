#!/bin/sh
set -ex

APPID_BASE="com.mendeni.sonobus"
INSTALLER_PKG="SonoBusMendeniInstaller.pkg"

BUILD_DIR="build"

APP_ROOT="pkgroot-app"
VST3_ROOT="pkgroot-vst3"

APP_SRC="../build/SonoBusMendeni_artefacts/Release/Standalone/SonoBusMendeni.app"
VST3_SRC="../build/SonoBusMendeni_artefacts/Release/VST3/SonoBusMendeni.vst3"

VERSION=$(/usr/libexec/PlistBuddy -c "Print :CFBundleShortVersionString" "../build/SonoBusMendeni_artefacts/Release/Standalone/SonoBusMendeni.app/Contents/Info.plist")

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

rm -rf "$APP_ROOT" "$VST3_ROOT"

mkdir -p "$APP_ROOT/Applications"
mkdir -p "$VST3_ROOT/Library/Audio/Plug-Ins/VST3"

cp -a "$APP_SRC" "$APP_ROOT/Applications"
cp -a "$VST3_SRC" "$VST3_ROOT/Library/Audio/Plug-Ins/VST3"

cp -a ../LICENSE resources/license.txt
cat ../LICENSE_EXCEPTION >> resources/license.txt

chmod -R 755 "$APP_ROOT" "$VST3_ROOT"

echo "Building component packages..."

pkgbuild \
  --root "$APP_ROOT" \
  --identifier "$APPID_BASE.pkg.app" \
  --version "$VERSION" \
  --install-location / \
  "$BUILD_DIR/sonobus-app.pkg"

pkgbuild \
  --root "$VST3_ROOT" \
  --identifier "$APPID_BASE.pkg.vst3" \
  --version "$VERSION" \
  --install-location / \
  "$BUILD_DIR/sonobus-vst3.pkg"

echo "Building $INSTALLER_PKG ..."

productbuild \
  --distribution distribution.xml \
  --resources resources \
  --package-path "$BUILD_DIR" \
  "$BUILD_DIR/$INSTALLER_PKG"

echo "Done."
echo "Installer created at: $BUILD_DIR/$INSTALLER_PKG"
