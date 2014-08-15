<?xml version="1.0" encoding="utf-8"?>

<!-- 4D supports XSLT 1.0 -->
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
     xmlns:svg="http://www.w3.org/2000/svg"
     xmlns:str="http://exslt.org/strings">     
    
	<!-- possible values are html, text, xhtml -->
	<xsl:output method="text" indent="no" />
    
	<xsl:param name="str1" select="'param1'" />
    
	<!-- this means you match at the root node -->
	<xsl:template match="/" >
       
		<!--print the param value -->	   
        <xsl:text>param (str1):</xsl:text>
        <xsl:value-of select="$str1" />
        <xsl:text>&#xD;</xsl:text>
		
		<!--print function results and node values -->
        <xsl:for-each select="/svg:svg/svg:g/svg:path">
			<xsl:value-of select="concat('stroke (', position(),'):')" />
            <xsl:value-of select="@stroke" />
			<xsl:text>&#xD;</xsl:text>
        </xsl:for-each>

	</xsl:template>
    
</xsl:stylesheet>