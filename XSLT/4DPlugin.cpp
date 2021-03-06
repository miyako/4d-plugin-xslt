/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : XSLT
 #	author : miyako
 #	2016/09/20
 #
 # --------------------------------------------------------------------------------*/

#include "4DPlugin.h"

std::mutex mutexXslt;

void OnStartup()
{
	xmlInitMemory();
	exsltRegisterAll();
}

void OnExit()
{
    xsltCleanupGlobals();
    xmlCleanupParser();
}

#pragma mark -

namespace XSLT
{
	void parse(char *xmlptr, int xmlsize,
						 char *xslptr, int xslsize,
						 ARRAY_TEXT &names, ARRAY_TEXT &values, C_LONGINT &extraoptions,
						 CUTF8String &result, BOOL xmlIsFile, BOOL xslIsFile)
	{
		std::vector<CUTF8String> _params;
		std::vector<const char *> params;
		
		if(names.getSize() == values.getSize())
		{
			unsigned int i, size = values.getSize();
			CUTF8String name, value;
			size_t j = 0;
			for(i = 0; i < size; ++i)
			{
				names.copyUTF8StringAtIndex(&name, i);
				values.copyUTF8StringAtIndex(&value, i);
				if(name.length() != 0)
				{
					_params.push_back(name);
					_params.push_back(value);
					params.push_back((const char *)_params[j++].c_str());
					params.push_back((const char *)_params[j].c_str());
				}
			}
		}
		params.push_back(NULL);
		
		int options = XSLT_PARSE_OPTIONS|extraoptions.getIntValue();
		
		xmlDocPtr xmlDoc = 0;
		xmlDocPtr xslDoc = 0;
		xmlDocPtr xmlOutDoc = 0;
		xsltStylesheetPtr stylesheet = 0;
		
		if(xmlIsFile)
		{
			xmlDoc = xmlParseFile((const char *)xmlptr);
		}else
		{
			xmlDoc = xmlParseMemory(xmlptr, xmlsize);
		}
		
		if(xmlDoc)
		{
			xmlXIncludeProcessFlags(xmlDoc, options);
			
			if(xslIsFile)
			{
				stylesheet = xsltParseStylesheetFile((const xmlChar *)xslptr);
			}else
			{
				xslDoc = xmlParseMemory(xslptr, xslsize);
				if(xslDoc)
				{
					xmlXIncludeProcessFlags(xslDoc, options);
					stylesheet = xsltParseStylesheetDoc(xslDoc);
				}
			}
			
			if (stylesheet)
			{
				xsltTransformContextPtr ctxt;
				ctxt = xsltNewTransformContext(stylesheet, xmlDoc);
				
				void (*_PA_YieldAbsolute)(void) = PA_YieldAbsolute;
				xmlOutDoc = xsltApplyStylesheetUser (stylesheet, xmlDoc, &params[0], NULL, NULL, ctxt, _PA_YieldAbsolute);
				
				if(xmlOutDoc)
				{
					xmlOutputBufferPtr outputBuffer = xmlAllocOutputBuffer(0);
					// mysteriously, 0 is returned
					// http://xmlsoft.org/XSLT/html/libxslt-xsltutils.html#xsltSaveResultTo
					xsltSaveResultTo (outputBuffer, xmlOutDoc, stylesheet);
					size_t resultLength = xmlOutputBufferGetSize(outputBuffer);
					
					if (resultLength)
					{
						result = CUTF8String((const uint8_t *)xmlOutputBufferGetContent(outputBuffer), resultLength);
					}
					xmlOutputBufferClose(outputBuffer);
				}
				
			}
			
		}
		
		if(stylesheet)
		{
			//will free xslDoc too
			xsltFreeStylesheet(stylesheet);
		}else{
			if(xslDoc) xmlFreeDoc(xslDoc);
		}

		if(xmlDoc) xmlFreeDoc(xmlDoc);
		if(xmlOutDoc) xmlFreeDoc(xmlOutDoc);
		
	}
	
}

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	try
	{
		PA_long32 pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
		case kInitPlugin :
		case kServerInitPlugin :
			OnStartup();
			break;
			
        case kDeinitPlugin :
            OnExit();
            break;
			
// --- XSLT

		case 1 :
			XSLT_Apply_stylesheet(pResult, pParams);
			break;

		case 2 :
			XSLT_Apply_stylesheet_data(pResult, pParams);
			break;

	}
}

// ------------------------------------- XSLT -------------------------------------

#pragma mark -

BOOL is_file_path(C_TEXT &str)
{
	PA_Variable	params[1];
	params[0] = PA_CreateVariable(eVK_Unistring);
	PA_Unistring path = PA_CreateUnistring((PA_Unichar *)str.getUTF16StringPtr());
	PA_SetStringVariable(&params[0], &path);
	BOOL result = (1 == PA_GetLongintVariable(PA_ExecuteCommandByID(476, params, 1)));
	PA_ClearVariable(&params[0]);
	
	return result;
}

#pragma mark -

void XSLT_Apply_stylesheet(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	ARRAY_TEXT Param3;
	ARRAY_TEXT Param4;
	C_LONGINT Param5;
	C_TEXT returnValue;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	
	CUTF8String xmlIn, xslIn, xsltOut;
	
	BOOL xmlIsFile = is_file_path(Param1);
	BOOL xslIsFile = is_file_path(Param2);
	
#if VERSIONMAC
	if(xmlIsFile) Param1.convertPath();
	if(xslIsFile) Param2.convertPath();
#endif
	
	Param1.copyUTF8String(&xmlIn);
	Param2.copyUTF8String(&xslIn);
	
	XSLT::parse((char *)xmlIn.c_str(), (int)xmlIn.size(),
							(char *)xslIn.c_str(), (int)xslIn.size(),
							Param3, Param4, Param5,
							xsltOut, xmlIsFile, xslIsFile);
	
	returnValue.setUTF8String(&xsltOut);
	returnValue.setReturn(pResult);
}

void XSLT_Apply_stylesheet_data(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_BLOB Param1;
	C_BLOB Param2;
	ARRAY_TEXT Param3;
	ARRAY_TEXT Param4;
	C_LONGINT Param5;
	C_BLOB returnValue;

	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);

	CUTF8String xsltOut;
	
	XSLT::parse((char *)Param1.getBytesPtr(), (int)Param1.getBytesLength(),
							(char *)Param2.getBytesPtr(), (int)Param2.getBytesLength(),
							Param3, Param4, Param5,
							xsltOut, false, false);

	returnValue.setBytes((const uint8_t *)xsltOut.c_str(), xsltOut.size());
	returnValue.setReturn(pResult);
}
