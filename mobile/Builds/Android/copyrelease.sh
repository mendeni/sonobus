#!/bin/bash

if [ x"$1" = "x" ] ; then
  echo "Usage: $0 version"
  exit 2
fi

VERSION=$1

FNAME=sonobus-$VERSION-android.apk
FNAMEAAB=sonobus-$VERSION.aab

cp -v app/build/outputs/apk/release_/release/app-release_-release.apk ../../../release/android/$FNAME

cp -v app/build/outputs/bundle/release_Release/app-release_-release.aab ../../../release/android/$FNAMEAAB


# now make a zip of the symbols
DFNAME=debug_${FNAME/apk/zip}
rm -f ../../../release/android/${DFNAME}

#cd app/build/intermediates/cmake/release_Release/obj
cd app/build/intermediates/merged_native_libs/release_Release/mergeRelease_ReleaseNativeLibs/out/lib

#zip -r ../../../../../../../../../release/android/${DFNAME} */*.so
zip -r ../../../../../../../../../../../release/android/${DFNAME} */libjuce_jni.so
