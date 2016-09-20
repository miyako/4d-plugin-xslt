4d-plugin-xslt
==============

4D implementation of [libxslt] (http://xmlsoft.org/libxslt/). 64 bits OS X and Windows.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🆗|🆗|🆗|🆗|


##New in 1.1

* New plugin architecture for v14+.
* BLOB API.
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
$xslPath:=Get 4D folder(Current Resources folder)+"sample.xsl"
$xmlPath:=Get 4D folder(Current Resources folder)+"apple.svg"

$outPath:=System folder(Desktop)+Generate UUID

ARRAY TEXT($paramNames;1)
ARRAY TEXT($paramValues;1)

XSLT SET PARAMETER("str1";"'test'")

XSLT APPLY TRANSFORMATION($xmlPath;$xslPath;$outPath)

//do the same with the plugin:

ARRAY TEXT($paramNames;1)
ARRAY TEXT($paramValues;1)

$paramNames{1}:="str1"
$paramValues{1}:="'test'"

$xml:=XSLT Apply stylesheet ($xmlPath;$xslPath;$paramNames;$paramValues)

SET TEXT TO PASTEBOARD($xml)
```
