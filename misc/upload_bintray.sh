#!/bin/bash

# Upload deb file to bintray.com script
# 
# == Example ==
#
# The example below shows how to upload a picture called sweeping_the_rock.png 
# to a Picasa Web Album with the title "Sweeping the rock":
#
# == Example Code ==
# curl --silent --request POST --data-binary "@sweeping_the_rock.png" 
# --header "Slug: Sweeping the rock" 
# --header "Content-Type: image/png" 
# --header "Authorization: GoogleLogin auth=ABCDEFG" 
#          "http://picasaweb.google.com/data/feed/api/user/brad.gushue/albumid/5113621341847124417" | tidy -xml -indent -quiet

# Load version from configure.ac
VERSION=`cat ../configure.ac | grep AC_INIT | awk '{print $2}' | sed -e 's/\[\|\]\|,//g'`
echo "JaneClone version is ${VERSION}"

# Package
DEB_FILENAME="janeclone_${VERSION}_amd64.deb"

# .dsc file
DSC_FILENAME="janeclone_${VERSION}.dsc"
# source file
SRC_FILENAME="janeclone_${VERSION}.tar.gz"
# other files
BLD_FILENAME="janeclone_${VERSION}_amd64.build"
CHG_FILENAME="janeclone_${VERSION}_amd64.changes"

echo "File name is ${DEB_FILENAME}"

if ! test -e ../${DEB_FILENAME}; then
    echo "${DEB_FILENAME} is not created abort...";
    exit 1;
fi

CURL="curl -v --user hiroyuki-nagata:${BINTRAY_TOKEN}"
METHOD="-X PUT --data-binary @- "
API="https://api.bintray.com"

#
# Here upload executing !
#

# .deb file
RESOURCE="/content/hiroyuki-nagata/deb/JaneClone/${VERSION}/${DEB_FILENAME};publish=1?override=1"
cat ../${DEB_FILENAME} | ${CURL} ${METHOD} ${API}${RESOURCE}
# .dsc file
RESOURCE="/content/hiroyuki-nagata/deb/JaneClone/${VERSION}/${DSC_FILENAME};publish=1?override=1"
cat ../${DSC_FILENAME} | ${CURL} ${METHOD} ${API}${RESOURCE}
# source file
RESOURCE="/content/hiroyuki-nagata/deb/JaneClone/${VERSION}/${SRC_FILENAME};publish=1?override=1"
cat ../${SRC_FILENAME} | ${CURL} ${METHOD} ${API}${RESOURCE}
# other files
RESOURCE="/content/hiroyuki-nagata/deb/JaneClone/${VERSION}/${BLD_FILENAME};publish=1?override=1"
cat ../${BLD_FILENAME} | ${CURL} ${METHOD} ${API}${RESOURCE}
RESOURCE="/content/hiroyuki-nagata/deb/JaneClone/${VERSION}/${CHG_FILENAME};publish=1?override=1"
cat ../${CHG_FILENAME} | ${CURL} ${METHOD} ${API}${RESOURCE}