4d-plugin-xslt
==============

4D implementation of [libxslt] (http://xmlsoft.org/libxslt/). 64 bits OS X and Windows.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🆗|🆗|🆗|🆗|

Commands
---

```c
// --- XSLT
XSLT_Apply_stylesheet
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
