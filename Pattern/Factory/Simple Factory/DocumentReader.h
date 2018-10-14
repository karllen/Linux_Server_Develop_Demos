#pragma once
#include <iostream>
typedef enum ReadType
{
    WORD,
    HTML,
    PDF,
    UNKNOWN
}; 

class CReadDocumentShowHandler
{
public:
    CReadDocumentShowHandler();
    virtual ~CReadDocumentShowHandler();
public:
    virtual bool ReadDocumentShow() = 0;
};


class CReadHtmlShowHandler :
    public CReadDocumentShowHandler
{
public:
    CReadHtmlShowHandler();
    virtual ~CReadHtmlShowHandler();
public:
    virtual  bool ReadDocumentShow();
};

class CReadPdfShowHandler : 
    public CReadDocumentShowHandler
{
public:
    CReadPdfShowHandler();
    virtual ~CReadPdfShowHandler();
public:
    virtual  bool ReadDocumentShow();
};


class CReadWordShowHandler :
    public CReadDocumentShowHandler
{
public:
    CReadWordShowHandler();
    virtual ~CReadWordShowHandler();
public:
    virtual  bool ReadDocumentShow();
};


CReadDocumentShowHandler::CReadDocumentShowHandler()
{
}


CReadDocumentShowHandler::~CReadDocumentShowHandler()
{
}


CReadHtmlShowHandler::CReadHtmlShowHandler()
{
}


CReadHtmlShowHandler::~CReadHtmlShowHandler()
{
}

bool CReadHtmlShowHandler::ReadDocumentShow()
{
    try
    {
        //operation ...
        std::cout << " Read Html Document Operation ..." <<std::endl;
        return true;
    }
    catch (...)
    {
        return false;
    }
}


CReadPdfShowHandler::CReadPdfShowHandler()
{
}


CReadPdfShowHandler::~CReadPdfShowHandler()
{
}

bool CReadPdfShowHandler::ReadDocumentShow()
{
    try
    {
        std::cout << " Read PDF Document Operation ..." << std::endl;
        return true;
    }
    catch (...)
    {
        return false;
    }
}


CReadWordShowHandler::CReadWordShowHandler()
{
}


CReadWordShowHandler::~CReadWordShowHandler()
{
}

bool CReadWordShowHandler::ReadDocumentShow()
{
    try
    {
        std::cout << " Read Word Document Operation ..." << std::endl;
        return true;
    }
    catch (...)
    {
        return false;
    }
}