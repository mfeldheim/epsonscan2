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
//  ESPropertyKeys.h -- template and derived ESC/I ESC/I-2 protocol commands
#pragma once

       
#include "../es2CommnoType.h"
STATIC_CONST_KEY kESVersion = ES_STRING("version");
STATIC_CONST_KEY kESWorkFolder = ES_STRING("workFolder");
STATIC_CONST_KEY kESInterruptionEnabled = ES_STRING("interruptionEnabled");
STATIC_CONST_KEY kESErrorStatus = ES_STRING("errorStatus");
STATIC_CONST_KEY kESBatteryStatus = ES_STRING("batteryStatus");
STATIC_CONST_KEY kESSensorGlassStatus = ES_STRING("sensorGlassStatus");
STATIC_CONST_KEY kESScannerPositionStatus = ES_STRING("scannerPositionStatus");
STATIC_CONST_KEY kESWarningStatus = ES_STRING("warningStatus");
STATIC_CONST_KEY kESUnavailableScanParameterStatus = ES_STRING("unavailableScanParameterStatus");
STATIC_CONST_KEY kESAuthentication = ES_STRING("authentication");
STATIC_CONST_KEY kESAuthenticationEnabled = ES_STRING("authenticationEnabled");
STATIC_CONST_KEY kESLengthPadding = ES_STRING("lengthPadding");
STATIC_CONST_KEY kESAutoFeedingMode = ES_STRING("autoFeedingMode");
STATIC_CONST_KEY kESContinuousAutoFeedingMode = ES_STRING("continuousAutoFeedingMode");
STATIC_CONST_KEY kESAutoFeedingModeTimeout = ES_STRING("autoFeedingModeTimeout");
STATIC_CONST_KEY kESProductName = ES_STRING("productName");
STATIC_CONST_KEY kESSerialNumber = ES_STRING("serialNumber");
STATIC_CONST_KEY kESAuthUsername = ES_STRING("authUsername");
STATIC_CONST_KEY kESAuthPassword = ES_STRING("authPassword");
STATIC_CONST_KEY kESDefaultPasswordType = ES_STRING("defaultPasswordType");
STATIC_CONST_KEY kESAdminLock = ES_STRING("adminLock");
STATIC_CONST_KEY kESAdminLockEnabled = ES_STRING("adminLockEnabled");
STATIC_CONST_KEY kESAdminLockPassword = ES_STRING("adminLockPassword");
STATIC_CONST_KEY kESFunctionalUnitType = ES_STRING("functionalUnitType");
STATIC_CONST_KEY kESXResolution = ES_STRING("xResolution");
STATIC_CONST_KEY kESYResolution = ES_STRING("yResolution");
STATIC_CONST_KEY kESOpticalResolution = ES_STRING("opticalResolution");
STATIC_CONST_KEY kESMaxScanSize = ES_STRING("maxScanSize");
STATIC_CONST_KEY kESScanArea = ES_STRING("scanArea");
STATIC_CONST_KEY kESScanAreaInPixel = ES_STRING("scanAreaInPixel");
STATIC_CONST_KEY kESScanSize = ES_STRING("scanSize");
STATIC_CONST_KEY kESScanSizeInPixel = ES_STRING("scanSizeInPixel");
STATIC_CONST_KEY kESXOffsetMargin = ES_STRING("xOffsetMargin");
STATIC_CONST_KEY kESYOffsetMargin = ES_STRING("yOffsetMargin");
STATIC_CONST_KEY kESColorFormat = ES_STRING("colorFormat");
STATIC_CONST_KEY kESColorCounterType = ES_STRING("colorCounterType");
STATIC_CONST_KEY kESBitsPerPixel = ES_STRING("bitsPerPixel");
STATIC_CONST_KEY kESHalftone = ES_STRING("halftone");
STATIC_CONST_KEY kESGammaMode = ES_STRING("gammaMode");
STATIC_CONST_KEY kESGammaTableMono = ES_STRING("gammaTableMono");
STATIC_CONST_KEY kESGammaTableRed = ES_STRING("gammaTableRed");
STATIC_CONST_KEY kESGammaTableGreen = ES_STRING("gammaTableGreen");
STATIC_CONST_KEY kESGammaTableBlue = ES_STRING("gammaTableBlue");
STATIC_CONST_KEY kESColorMatrix = ES_STRING("colorMatrix");
STATIC_CONST_KEY kESThreshold = ES_STRING("threshold");
STATIC_CONST_KEY kESQuietMode = ES_STRING("quietMode");
STATIC_CONST_KEY kESBufferSize = ES_STRING("bufferSize");
STATIC_CONST_KEY kESDuplexType = ES_STRING("duplexType");
STATIC_CONST_KEY kESDuplex = ES_STRING("duplex");
STATIC_CONST_KEY kESDoubleFeedDetection = ES_STRING("doubleFeedDetection");
STATIC_CONST_KEY kESMinDoubleFeedDetectionRangeLength = ES_STRING("minDoubleFeedDetectionRangeLength");
STATIC_CONST_KEY kESDoubleFeedDetectionRangeOffset = ES_STRING("doubleFeedDetectionRangeOffset");
STATIC_CONST_KEY kESDoubleFeedDetectionRangeLength = ES_STRING("doubleFeedDetectionRangeLength");
STATIC_CONST_KEY kESLenghtDoubleFeedDetection = ES_STRING("lengthDoubleFeedDetection");
STATIC_CONST_KEY kESLengthDoubleFeedDetectionLength = ES_STRING("lengthDoubleFeedDetectionLength");
STATIC_CONST_KEY kESImageDoubleFeedDetection = ES_STRING("imageDoubleFeedDetection");
STATIC_CONST_KEY kESImagePaperProtection = ES_STRING("imagePaperProtection");
STATIC_CONST_KEY kESCarrierSheetDetection = ES_STRING("carrierSheetDeteciton");
STATIC_CONST_KEY kESAutoCropping = ES_STRING("autoCropping");
STATIC_CONST_KEY kESAutoCroppingInscribed = ES_STRING("autoCroppingInscribed");
STATIC_CONST_KEY kESCroppableResolutions = ES_STRING("croppableResolutions");
STATIC_CONST_KEY kESCroppingSize = ES_STRING("croppingSize");
STATIC_CONST_KEY kESPagesToBeScanned = ES_STRING("pagesToBeScanned");
STATIC_CONST_KEY kESDocumentLoaded = ES_STRING("documentLoaded");
STATIC_CONST_KEY kESDocumentSeparation = ES_STRING("documentSeparation");
STATIC_CONST_KEY kESCardScanning = ES_STRING("cardScanning");
STATIC_CONST_KEY kESCleaning = ES_STRING("cleaning");
STATIC_CONST_KEY kESCalibration = ES_STRING("calibration");
STATIC_CONST_KEY kESDetectedDocumentSize = ES_STRING("detectedDocumentSize");
STATIC_CONST_KEY kESEdgeFillWidthRight = ES_STRING("edgeFillWidthRight");
STATIC_CONST_KEY kESEdgeFillWidthTop = ES_STRING("edgeFillWidthTop");
STATIC_CONST_KEY kESEdgeFillWidthLeft = ES_STRING("edgeFillWidthLeft");
STATIC_CONST_KEY kESEdgeFillWidthBottom = ES_STRING("edgeFillWidthBottom");
STATIC_CONST_KEY kESEdgeFillColor = ES_STRING("edgeFillColor");
STATIC_CONST_KEY kESDigitalICE = ES_STRING("digitalICE");
STATIC_CONST_KEY kESFilmType = ES_STRING("filmType");
STATIC_CONST_KEY kESScanningMode = ES_STRING("scanningMode");
STATIC_CONST_KEY kESLaminatedPaperMode = ES_STRING("laminatedPaperMode");
STATIC_CONST_KEY kESBGColor = ES_STRING("BGColor");
STATIC_CONST_KEY kESWarmingUp = ES_STRING("warmingUp");
STATIC_CONST_KEY kESButtonStatus = ES_STRING("buttonStatus");
STATIC_CONST_KEY kESLampMode = ES_STRING("lampMode");
STATIC_CONST_KEY kESPowerSaveTime = ES_STRING("powerSaveTime");
STATIC_CONST_KEY kESMaxFocus = ES_STRING("maxFocus");
STATIC_CONST_KEY kESMinFocus = ES_STRING("minFocus");
STATIC_CONST_KEY kESFocus = ES_STRING("focus");
STATIC_CONST_KEY kESSimplexScanCounter = ES_STRING("simplexScanCounter");
STATIC_CONST_KEY kESDuplexScanCounter = ES_STRING("duplexScanCounter");
STATIC_CONST_KEY kESSimplexCardScanCounter = ES_STRING("simplexCardScanCounter");
STATIC_CONST_KEY kESDuplexCardScanCounter = ES_STRING("duplexCardScanCounter");
STATIC_CONST_KEY kESLamp1Counter = ES_STRING("lamp1Counter");
STATIC_CONST_KEY kESLamp2Counter = ES_STRING("lamp2Counter");
STATIC_CONST_KEY kESPickupRollerCounter = ES_STRING("pickupRollerCounter");
STATIC_CONST_KEY kESSeparationPadCounter = ES_STRING("separationPadCounter");
STATIC_CONST_KEY kESRetardRollerCounter = ES_STRING("retardRollerCounter");
STATIC_CONST_KEY kESScanCounter = ES_STRING("scanCounter");
STATIC_CONST_KEY kESCaptureCommandSupported = ES_STRING("captureCommandSupported");
STATIC_CONST_KEY kESShouldIgnoreCancelFromScanner = ES_STRING("shouldIgnoreCancelFromScanner");
STATIC_CONST_KEY kESGuidePosition = ES_STRING("guidePosition");
STATIC_CONST_KEY kESGuidePositionFB = ES_STRING("guidePositionFB");
STATIC_CONST_KEY kESGuidePositionADF = ES_STRING("guidePositionADF");
STATIC_CONST_KEY kESGuidelessADF = ES_STRING("guidelessADF");
STATIC_CONST_KEY kESDisableJobContinue = ES_STRING("disableJobContinue");
STATIC_CONST_KEY kESDisableKeepingCapture = ES_STRING("disableKeepingCapture");
STATIC_CONST_KEY kESMaxImagePixels = ES_STRING("maxImagePixels");
STATIC_CONST_KEY kESMaxScanSizeInLongLength = ES_STRING("maxScanSizeInLongLength");
STATIC_CONST_KEY kESMaxLongLengthTable = ES_STRING("maxLongLengthTable");
STATIC_CONST_KEY kESMinScanSize = ES_STRING("minScanSize");
STATIC_CONST_KEY kESImageFormat = ES_STRING("imageFormat");
STATIC_CONST_KEY kESColorMatrixMode = ES_STRING("colorMatrixMode");
STATIC_CONST_KEY kESSkewCorrection = ES_STRING("skewCorrection");
STATIC_CONST_KEY kESJPEGQuality = ES_STRING("JPEGQuality");
STATIC_CONST_KEY kESPaperEndDetection = ES_STRING("paperEndDetection");
STATIC_CONST_KEY kESOverScan = ES_STRING("overScan");
STATIC_CONST_KEY kESOverScanForCropping = ES_STRING("overScanForCropping");
STATIC_CONST_KEY kESPassportCarrierSheetScan = ES_STRING("passportCarrierSheetScan");
STATIC_CONST_KEY kESPowerOffTime = ES_STRING("powerOffTime");
STATIC_CONST_KEY kESPowerOffTime2nd = ES_STRING("powerOffTime2nd");
STATIC_CONST_KEY kESFirstPCConnectionDate = ES_STRING("firstPCConnectionDate");
STATIC_CONST_KEY kESDocumentFeederLamp1Counter = ES_STRING("documentFeederLamp1Counter");
STATIC_CONST_KEY kESDocumentFeederLamp2Counter = ES_STRING("documentFeederLamp2Counter");
STATIC_CONST_KEY kESPaperJamCounter = ES_STRING("paperJamCounter");
STATIC_CONST_KEY kESUltraSonicDoubleFeedCounter = ES_STRING("ultraSonicDoubleFeedCounter");
STATIC_CONST_KEY kESLengthDoubleFeedCounter = ES_STRING("lengthDoubleFeedCounter");
STATIC_CONST_KEY kESRollerKitCounter = ES_STRING("rollerKitCounter");
STATIC_CONST_KEY kESImageDoubleFeedCounter = ES_STRING("imageDoubleFeedCounter");
STATIC_CONST_KEY kESPaperProtectionCounter = ES_STRING("paperProtectionCounter");
STATIC_CONST_KEY kESPaperProtectionOverflowCounter = ES_STRING("paperProtectionOverflowCounter");
STATIC_CONST_KEY kESPaperProtectionDistortionCounter= ES_STRING("paperProtectionDistortionCounter");
STATIC_CONST_KEY kESSpecialDocumentCounter = ES_STRING("specialDocumentCounter");
STATIC_CONST_KEY kESPassportCarrierSheetCounter = ES_STRING("passportCarrierSheetCounter");
STATIC_CONST_KEY kESFlatbedLamp1Counter = ES_STRING("flatbedLamp1Counter");
STATIC_CONST_KEY kESFlatbedLamp2Counter = ES_STRING("flatbedLamp2Counter");
STATIC_CONST_KEY kESDocumentTopCorrectionFront = ES_STRING("documentTopCorrectionFront");
STATIC_CONST_KEY kESDocumentTopCorrectionBack = ES_STRING("documentTopCorrectionBack");
STATIC_CONST_KEY kESDocumentDriveCorrectionFront = ES_STRING("documentDriveCorrectionFront");
STATIC_CONST_KEY kESDocumentDriveCorrectionBack = ES_STRING("documentDriveCorrectionBack");
STATIC_CONST_KEY kESLightIntensityBack = ES_STRING("lightIntensityBack");
STATIC_CONST_KEY kESLightIntensityFB = ES_STRING("lightIntensityFB");
STATIC_CONST_KEY kESDocumentFeederBGLevelFront = ES_STRING("documentFeederBGLevelFront");
STATIC_CONST_KEY kESDocumentFeederBGLevelBack = ES_STRING("documentFeederBGLevelBack");
STATIC_CONST_KEY kESPickupRollerLifeLimit = ES_STRING("pickupRollerLifeLimit");
STATIC_CONST_KEY kESSeparationPadLifeLimit = ES_STRING("separationPadLifeLimit");
STATIC_CONST_KEY kESRollerKitLifeLimit = ES_STRING("rollerKitLifeLimit");
STATIC_CONST_KEY kESRetardRollerLifeLimit = ES_STRING("retardRollerLifeLimit");
STATIC_CONST_KEY kESPickupRollerNearend = ES_STRING("pickupRollerNearend");
STATIC_CONST_KEY kESSeparationPadNearend = ES_STRING("separationPadNearend");
STATIC_CONST_KEY kESRetardRollerNearend = ES_STRING("retardRollerNearend");
STATIC_CONST_KEY kESRollerKitNearend = ES_STRING("rollerKitNearend");
STATIC_CONST_KEY kESSensorGlassDirtSensitivity = ES_STRING("sensorGlassDirtSensitivity");
STATIC_CONST_KEY kESClientApplication = ES_STRING("clientApplication");
STATIC_CONST_KEY kESDirectPowerOn = ES_STRING("directPowerOn");
STATIC_CONST_KEY kESNonConnectPowerOff = ES_STRING("nonConnectPowerOff");
STATIC_CONST_KEY kESADFPaperProtection = ES_STRING("adfPaperProtection");
STATIC_CONST_KEY kESBehaviorWhenDoubleFeed = ES_STRING("behaviorWhenDoubleFeed");
STATIC_CONST_KEY kESCleaningWarningNotifyCount = ES_STRING("cleaningWarningNotifyCount");
STATIC_CONST_KEY kESRollerKitNotifyCount = ES_STRING("rollerKitNotifyCount");
STATIC_CONST_KEY kESRetardRollerNotifyCount = ES_STRING("retardRollerNotifyCount");
STATIC_CONST_KEY kESSeparationPadNotifyCount = ES_STRING("separationPadNotifyCount");
STATIC_CONST_KEY kESPickupRollerNotifyCount = ES_STRING("pickupRollerNotifyCount");
STATIC_CONST_KEY kESCleaningWarningCounter = ES_STRING("cleaningWarningCounter");
STATIC_CONST_KEY kESCleaningWarningNotify = ES_STRING("cleaningWarningNotify");
STATIC_CONST_KEY kESDetectColorTypeEnabled = ES_STRING("detectColorTypeEnabled");
STATIC_CONST_KEY kESDetectBlankPageEnabled = ES_STRING("detectBlankPageEnabled");
STATIC_CONST_KEY kESDetectBlankPageLevel = ES_STRING("detectBlankPageLevel");
STATIC_CONST_KEY kESSkipImageEnhancement = ES_STRING("skipImageEnhancement");
STATIC_CONST_KEY kESErrorCode = ES_STRING("errorCode");
STATIC_CONST_KEY kESBGLevelKeyRed = ES_STRING("bgLevelKeyRed");
STATIC_CONST_KEY kESBGLevelKeyRedWidth = ES_STRING("bgLevelKeyRedWidth");
STATIC_CONST_KEY kESBGLevelKeyGreen = ES_STRING("bgLevelKeyGreen");
STATIC_CONST_KEY kESBGLevelKeyGreenWidth = ES_STRING("bgLevelKeyGreenWidth");
STATIC_CONST_KEY kESBGLevelKeyBlue = ES_STRING("bgLevelKeyBlue");
STATIC_CONST_KEY kESBGLevelKeyBlueWidth = ES_STRING("bgLevelKeyBlueWidth");
STATIC_CONST_KEY kESBGLevelKeyMono = ES_STRING("bgLevelKeyMono");
STATIC_CONST_KEY kESBGLevelKeyMonoWidth = ES_STRING("bgLevelKeyMonoWidth");
STATIC_CONST_KEY kESBackgroundRemoval = ES_STRING("backgroundRemoval");
STATIC_CONST_KEY kESBrightness = ES_STRING("brightness");
STATIC_CONST_KEY kESContrast = ES_STRING("contrast");
STATIC_CONST_KEY kESGammaScale = ES_STRING("gammaScale");
STATIC_CONST_KEY kESSharpnessFilter = ES_STRING("sharpnessFilterLevel");
STATIC_CONST_KEY kESADFLoadSupported = ES_STRING("adfLoadSupported");
