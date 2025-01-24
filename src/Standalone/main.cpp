//  Copyright (C) 2018-2022  SEIKO EPSON CORPORATION
//
//  License: LGPL-2.1+
//  Author : SEIKO EPSON CORPORATION
//
//  This file is part of the 'Epson Scan 2' package.
//	 This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.

//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//  
//  main.cpp -- template and derived ESC/I ESC/I-2 protocol commands

#ifndef NO_QTMODE
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#endif
#include "commandlinemode.h"
#include "../Include/Config.h"
#include "PathUtils.h"
void TranslateString(void){
#ifndef NO_QTMODE
    TranslationString& translation = TranslationString::GetString();
    translation.SetString();
#endif
}
int main(int argc, char *argv[])
{
    std::string strDst = EPSON_INSTALL_PATH;
#ifndef NO_QTMODE
#ifdef AKBMODE
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, "Resources/locale/");
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, DRIVER_NAME);
    strDst = strDst + "_";
#else
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, "Resources/locale/");
    ES_CMN_FUNCS::PATH::ES_CombinePath(strDst, strDst, "epsonscan2_");
#endif
#endif
    if(argc > 1){
        CommandLineMode* cmd_mode = new CommandLineMode();
        if(cmd_mode == NULL){
            return 0;
        }
        if(!cmd_mode->SelectMode(argc, (const char**)argv)){
#ifndef NO_QTMODE
            if(cmd_mode->SelectEditMode(argc, (const char**)argv)){
                QApplication a(argc, argv);
                QTranslator myappTranslator;
                if(!myappTranslator.load(strDst.c_str() + QLocale::system().name())){
                    myappTranslator.load((strDst + "en").c_str());
                }
                a.installTranslator(&myappTranslator);
                TranslateString();
                MainWindow w(argv[2]);
                w.show();
                return a.exec();
            }
#endif
        }
        int device_status = cmd_mode->IsGetStatus();
        delete cmd_mode;
        cmd_mode = NULL;
        return device_status;
    }else {
#ifndef NO_QTMODE
        QApplication a(argc, argv);
        QTranslator myappTranslator;
        if(!myappTranslator.load(strDst.c_str() + QLocale::system().name())){
            myappTranslator.load((strDst + "en").c_str());
        }
        a.installTranslator(&myappTranslator);
        TranslateString();
        MainWindow w("");
        w.show();
        return a.exec();
#else
        std::cout << "ERROR : Please specify options and setting(SF2) files." << std::endl;
#endif
    }
}
