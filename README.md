4d-plugin-xslt
==============

4D implementation of [libxslt] (http://xmlsoft.org/libxslt/). 64 bits OS X and Windows

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

###Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

###Syntax

```
xslt:=XSLT Apply stylesheet (xml;xsl;optionNames;optionValues;flags)
```

document|type|description
------------|------------|----
xml|TEXT|
xsl|TEXT|
optionNames|ARRAY TEXT|
optionValues|ARRAY TEXT|
flags|INT32|
document|TEXT|

```
xslt:=XSLT Apply stylesheet data (xml;xsl;optionNames;optionValues;flags)
```

document|type|description
------------|------------|----
xml|BLOB|
xsl|BLOB|
optionNames|ARRAY TEXT|
optionValues|ARRAY TEXT|
flags|INT32|
document|BLOB|

##New (Jan 2017)

The standard executables ``xsltproc`` and ``xmllint`` for ``LAUNCH EXTERNAL PROCESS`` are included.

```
PLATFORM PROPERTIES($platform)

$rootPath:=Get 4D folder(Database folder)+\
"plugins"+Folder separator+\
"XSLT.bundle"+Folder separator+\
"Contents"+Folder separator

Case of 
: ($platform=Mac OS)

SET ENVIRONMENT VARIABLE("_4D_OPTION_CURRENT_DIRECTORY";\
$rootPath+"MacOS"+Folder separator)

: ($platform=Windows)

SET ENVIRONMENT VARIABLE("_4D_OPTION_CURRENT_DIRECTORY";\
$rootPath+"Windows"+Folder separator)

  //64-bit version also available in Windows64

End case 

C_TEXT($stdIn;$stdOut;$stdErr)
LAUNCH EXTERNAL PROCESS("xsltproc"+Choose($platform=Windows;".exe";"");$stdIn;$stdOut;$stdErr)
```

##New in 1.1

* New plugin architecture for v14+.
* BLOB, File, Text API.
* In ``options`` you can pass a combination of instruction flags to alter how XML is parsed.

By default, the following flags are activated (libxslt behaviour):

```
XML_PARSE_NOENT | XML_PARSE_DTDLOAD | XML_PARSE_DTDATTR | XML_PARSE_NOCDATA
```

For full list of XML parser options, see the [libxml2](http://xmlsoft.org/html/libxml-parser.html) documentation.

###Examples

```
$xslPath:=Get 4D folder(Current resources folder)+"sample.xsl"
$xmlPath:=Get 4D folder(Current resources folder)+"apple.svg"

ARRAY TEXT($paramNames;1)
ARRAY TEXT($paramValues;1)

$paramNames{1}:="str1"
$paramValues{1}:="'test'"


Case of 
: (False)
  //text
$xml:=Document to text($xmlPath;"utf-8")
$xsl:=Document to text($xslPath;"utf-8")
$xslt:=XSLT Apply stylesheet ($xml;$xsl;$paramNames;$paramValues)

: (True)
  //blob
DOCUMENT TO BLOB($xmlPath;$xmlData)
DOCUMENT TO BLOB($xslPath;$xslData)
$xsltData:=XSLT Apply stylesheet data ($xmlData;$xslData;$paramNames;$paramValues)
$xslt:=Convert to text($xsltData;"utf-8")

: (False)
  //file
$xslt:=XSLT Apply stylesheet ($xmlPath;$xslPath;$paramNames;$paramValues)

End case 

SET TEXT TO PASTEBOARD($xslt)
```
