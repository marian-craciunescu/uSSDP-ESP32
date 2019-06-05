/*
  uSSDP.cpp - Library that implement SSDP protocol.
  Created by Filippo Sallemi, July 23, 2014.
  Released into the public domain.
*/

#include "uDevice.h"
#include <WiFi.h>

uDevice::uDevice() :
        _base(0),
        _mac(0),
        _presentationURL(0),
        _friendlyName(0),
        _modelName(0),
        _modelNumber(0),
        _serialNumber(0),
        _manufacturer(0),
        _manufacturerURL(0) {
    _deviceType = BASIC;
}

void uDevice::begin(const char *base, byte *mac, device_t deviceType) {
    _base = (char *) malloc(UUIDBASE_SIZE);
    _mac = (byte *) malloc(6);
    _presentationURL = (char *) malloc(PRESENTATIONURL_SIZE);
    _friendlyName = (char *) malloc(FRIENDLYNAME_SIZE);
    _modelName = (char *) malloc(MODELNAME_SIZE);
    _modelNumber = (version_t *) malloc(2);
    _serialNumber = (char *) malloc(SERIALNUMBER_SIZE);
    _manufacturer = (char *) malloc(MANUFACTURER_SIZE);
    _manufacturerURL = (char *) malloc(MANUFACTURERURL_SIZE);

    _deviceType = deviceType;
    _modelNumber->major = 0;
    _modelNumber->minor = 0;
    memcpy(_mac, mac, 6);
    strcpy(_base, base);
}

uDevice::~uDevice() {
    free(_base);
    free(_mac);
    free(_presentationURL);
    free(_friendlyName);
    free(_modelName);
    free(_modelNumber);
    free(_serialNumber);
    free(_manufacturer);
    free(_manufacturerURL);
}

String uDevice::uuid() {
    char _uuid[37];
    sprintf(_uuid, "%s-%02X%02X%02X%02X%02X%02X", _base, _mac[0], _mac[1], _mac[2], _mac[3], _mac[4], _mac[5]);
    return String(_uuid);
}


device_t uDevice::deviceType() {
    return _deviceType;
}

void uDevice::deviceType(device_t deviceType) {
    _deviceType = deviceType;
}


char *uDevice::presentationURL() {
    return _presentationURL;
}

void uDevice::presentationURL(char *presentationURL) {
    strcpy(_presentationURL, presentationURL);
}


char *uDevice::friendlyName() {
    return _friendlyName;
}

void uDevice::friendlyName(char *friendlyName) {
    strcpy(_friendlyName, friendlyName);
}


char *uDevice::modelName() {
    return _modelName;
}

void uDevice::modelName(char *modelName) {
    strcpy(_modelName, modelName);
}


version_t *uDevice::modelNumber() {
    return _modelNumber;
}

void uDevice::modelNumber(uint8_t major, uint8_t minor) {
    _modelNumber->major = major;
    _modelNumber->minor = minor;
}


char *uDevice::serialNumber() {
    return _serialNumber;
}

void uDevice::serialNumber(char *serialNumber) {
    strcpy(_serialNumber, serialNumber);
}


char *uDevice::manufacturer() {
    return _manufacturer;
}

void uDevice::manufacturer(char *manufacturer) {
    strcpy(_manufacturer, manufacturer);
}


char *uDevice::manufacturerURL() {
    return _manufacturerURL;
}

void uDevice::manufacturerURL(char *manufacturerURL) {
    strcpy(_manufacturerURL, manufacturerURL);
}
