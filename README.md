4d-plugin-xslt
==============

4D implementation of [libxslt] (http://xmlsoft.org/libxslt/). 64 bits OS X and Windows.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🆗|🆗|🆗|🆗|

##New (Jan 2017)

The standard executables ``xsltproc`` and ``xmllint`` for LAUNCH EXTERNAL PROCESS are included.

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

Commands
---

```c
// --- XSLT
XSLT Apply stylesheet
XSLT Apply stylesheet data
```

Examples
-------

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
