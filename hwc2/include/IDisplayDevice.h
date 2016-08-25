/*
// Copyright(c) 2016 Amlogic Corporation
*/
#ifndef IDISPLAY_DEVICE_H
#define IDISPLAY_DEVICE_H

#include <Dump.h>
#include <hardware/hwcomposer2.h>
#include <Hwcomposer.h>
#include <HwcLayer.h>

namespace android {
namespace amlogic {

// display config
class DisplayConfig {
public:
    DisplayConfig(int rr, int w, int h, int dpix, int dpiy)
        : mRefreshRate(rr),
          mWidth(w),
          mHeight(h),
          mDpiX(dpix),
          mDpiY(dpiy)
    {}
public:
    int getRefreshRate() const { return mRefreshRate; }
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
    int getDpiX() const { return mDpiX; }
    int getDpiY() const { return mDpiY; }
private:
    int mRefreshRate;
    int mWidth;
    int mHeight;
    int mDpiX;
    int mDpiY;
};


//  display device interface
class IDisplayDevice {
public:
    // display device type
    enum {
        DEVICE_PRIMARY = HWC_DISPLAY_PRIMARY,
        DEVICE_EXTERNAL = HWC_DISPLAY_EXTERNAL,
        DEVICE_VIRTUAL = HWC_DISPLAY_VIRTUAL,
        DEVICE_COUNT,
    };
    enum {
        DEVICE_DISCONNECTED = 0,
        DEVICE_CONNECTED,
    };
    enum {
        DEVICE_DISPLAY_OFF = 0,
        DEVICE_DISPLAY_ON,
        DEVICE_DISPLAY_STANDBY,
    };
public:
    IDisplayDevice() {}
    virtual ~IDisplayDevice() {}
public:
    virtual int32_t acceptDisplayChanges() = 0;
    virtual bool createLayer(hwc2_layer_t* outLayer) = 0;
    virtual bool destroyLayer(hwc2_layer_t layer) = 0;
    virtual int32_t getActiveConfig(hwc2_config_t* outConfig) = 0;
    virtual int32_t getChangedCompositionTypes(uint32_t* outNumElements, hwc2_layer_t* outLayers,
        int32_t* /*hwc2_composition_t*/ outTypes) = 0;
    virtual int32_t getClientTargetSupport(uint32_t width,
        uint32_t height, int32_t /*android_pixel_format_t*/ format,
        int32_t /*android_dataspace_t*/ dataspace) = 0;
    virtual int32_t getColorModes(uint32_t* outNumModes,
        int32_t* /*android_color_mode_t*/ outModes) = 0;
    virtual int32_t getDisplayAttribute(hwc2_config_t config,
        int32_t /*hwc2_attribute_t*/ attribute, int32_t* outValue) = 0;
    virtual int32_t getDisplayConfigs(uint32_t* outNumConfigs, hwc2_config_t* outConfigs) = 0;
    virtual int32_t getDisplayName(uint32_t* outSize,char* outName) = 0;
    virtual int32_t getDisplayRequests(int32_t* /*hwc2_display_request_t*/ outDisplayRequests,
        uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* /*hwc2_layer_request_t*/ outLayerRequests) = 0;
    virtual int32_t getDisplayType(int32_t* /*hwc2_display_type_t*/ outType) = 0;
    virtual int32_t getDozeSupport(int32_t* outSupport) = 0;
    virtual int32_t getHdrCapabilities(uint32_t* outNumTypes,
        int32_t* /*android_hdr_t*/ outTypes, float* outMaxLuminance,
        float* outMaxAverageLuminance, float* outMinLuminance) = 0;
    virtual int32_t getReleaseFences(uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outFences) = 0;
    virtual int32_t presentDisplay(int32_t* outRetireFence) = 0;
    virtual int32_t setActiveConfig(hwc2_config_t config) = 0;
    virtual int32_t setClientTarget(buffer_handle_t target,
        int32_t acquireFence, int32_t /*android_dataspace_t*/ dataspace, hwc_region_t damage) = 0;
    virtual int32_t setColorMode(int32_t /*android_color_mode_t*/ mode) = 0;
    virtual int32_t setColorTransform(const float* matrix, int32_t /*android_color_transform_t*/ hint) = 0;
    // virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) = 0;
    virtual int32_t setPowerMode(int32_t /*hwc2_power_mode_t*/ mode) = 0;
    virtual bool vsyncControl(bool enabled) = 0;
    virtual int32_t validateDisplay(uint32_t* outNumTypes, uint32_t* outNumRequests) = 0;
    virtual int32_t setCursorPosition(hwc2_layer_t layerId, int32_t x, int32_t y) = 0;

    // Virtual display.
    virtual int32_t createVirtualDisplay(uint32_t width, uint32_t height, int32_t* format, hwc2_display_t* outDisplay) = 0;
    virtual int32_t destroyVirtualDisplay(hwc2_display_t display) = 0;
    virtual int32_t setOutputBuffer(buffer_handle_t buffer, int32_t releaseFence) = 0;

    // Other Display methods
    virtual hwc2_display_t getId() const = 0;
    virtual bool isConnected() const = 0;

    // device related operations
    virtual bool initCheck() const = 0;
    virtual bool initialize() = 0;
    virtual void deinitialize() = 0;
    virtual const char* getName() const = 0;
    virtual int getDisplayId() const = 0;

    virtual HwcLayer* getLayerById(hwc2_layer_t layerId) = 0;

    virtual bool updateDisplayConfigs() = 0;

    //events
    virtual void onVsync(int64_t timestamp) = 0;

    virtual void dump(Dump& d) = 0;

};

}
}

#endif /* IDISPLAY_DEVICE_H */
