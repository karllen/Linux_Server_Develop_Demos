#pragma once
#include "DocumentReader.h"

class CReadDocumentFactory
{
public:
    CReadDocumentFactory();
    virtual ~CReadDocumentFactory();
public:
    CReadDocumentShowHandler * CreateReadDocHandler( int type );
};


CReadDocumentFactory::CReadDocumentFactory()
{
}


CReadDocumentFactory::~CReadDocumentFactory()
{
}

CReadDocumentShowHandler * CReadDocumentFactory::CreateReadDocHandler(int type)
{
    CReadDocumentShowHandler * pReadDocHandler = NULL;
    switch (type)
    {
    case WORD:
        pReadDocHandler = new CReadWordShowHandler();
        break;
    case HTML:
        pReadDocHandler = new CReadHtmlShowHandler();
        break;
    case PDF:
        pReadDocHandler = new CReadPdfShowHandler();
        break;
    default:
        break;
    }
    return pReadDocHandler != NULL ? pReadDocHandler : NULL;
}