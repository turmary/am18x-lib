// tary, 22:13 2015/10/26
#ifndef __9_USB_DEVICE_FRAMEWORK_H__
#define __9_USB_DEVICE_FRAMEWORK_H__

#include "am18x_type.h"

// 9.1 USB Device States
// 9.1.1 Visible Device States

// Note: USB devices perform a reset operation in response to
// reset signaling on the upstream port.
// When reset signaling has completed, the USB device is reset.

// Figure 9-1. Device State Diagram
typedef enum {
	// 9.1.1.1 Attached
	UD_STATE_Attached,


	// 9.1.1.2 Powered
	// Externally powered USB devices are termed self-powered.

	// It's not considered to be in the Powered state until
	// they are attached to the USB and Vbus is applied to the device.

	// the power maximum reported for that configuration is the maximum the
	// device will draw from Vbus in either mode.

	// A USB device must be able to be addressed within a specified time period
	// from when power is initially applied.

	// After an attachment to a port has been detected, the host may enable the port,
	// which will also reset the device attached to the port.
	UD_STATE_Powered,


	// 9.1.1.3 Default
	// After the device has been powered, it must not respond to any bus transactions
	// until it has received a reset from the bus.

	// After receiving a reset, the device is then addressable at the default address.
	UD_STATE_Default,


	// 9.1.1.4 Address
	// All USB devices use the default address when intially powered or after the device has been reset.

	// A USB device maintains its assigned address while suspended.

	// A USB device responds to requests on its default pipe whether the device is
	// currently assigned a unique address or is using the default address.
	UD_STATE_Address,


	// 9.1.1.5 Configured
	// Before a USB device's function may be used, the device must be configured.

	// From the device's perspective, configuration involves writing a non-zero value
	// to the device configuration register.

	// Configuring a device or changing an alternate setting causes all of the status
	// and configuration values associated with endpoints in the affected interfaces
	// to be set to their default values. This includes setting the data toggle
	// of any endpoint using data toggles to the value DATA0.
	UD_STATE_Configured,


	// 9.1.1.6 Suspended
	// When suspended, the USB device maintains any internal status,
	// including its address and configuration.

	// Bus activity may cease due to the host entering a suspend mode of
	// its own.

	// In addition, a USB device shall also enter the Suspended state
	// when the hub port it is attached to is disabled.
	// This is referred to as selective suspend.

	// The ability of a device to signal remote wakeup is optional.
	// If a USB device is capable of remote wakeup signaling,
	// the device must support the ability of the host to enable and disable
	// this capability. When the device is reset, remote wakeup signaling
	// must be disabled.
	UD_STATE_Suspended,
} usb_device_state_t;

typedef enum {
	UD_EVENT_Hub_Reset,
	UD_EVENT_Hub_Deconfigured,
	UD_EVENT_Hub_Configured,
	UD_EVENT_Bus_Inactive,
	UD_EVENT_Bus_Activity,
	UD_EVENT_Power_Interruption,
	UD_EVENT_Reset,
	UD_EVENT_Address_Assigned,
	UD_EVENT_Device_Deconfigured,
	UD_EVENT_Device_Configured,
} usb_device_event_t;


// 9.2 Generic USB Device Operations

// 1. Dynamic Attachment and Removel

// 2. Address Assignment

// 3. Configuration

// 4. Data Transfer

// 5. Power Management
// USB devices shall limit the power they consume from Vbus to 
// one unit load or less until configured.
// Depending on the power capabilities of the port to which
// the device is attached, a USB device may be able to draw up to
// five unit loads from Vbus after configuration.

// 6. Request Processing

// 6.1 Request Processing Timing
// USB sets an upper limit of 5 seconds as the upper limit for any command
// to be processed. This limit is not applicable in all instances.

// 6.2 Reset/Resume Recovery Time
// After a port is reset or resumed, the USB System Software is expected to
// provide a "recovery" interval of 10 ms before the device attached to
// the port is expected to respond to data tranfsers.

// 6.3 Set Address Processing
// After the reset/resume recovery interval, if a device receives
// a SetAddress() request, the device must be able to complete processing of
// the request and be able to successfully complete the Status stage of
// the request within 50 ms.
// After successful completion of the Status stage, the device is allowed
// a SetAddress() recovery interval of 2 ms. After the end of this interval,
// the device must be able to accept Setup packets addressed to the new address.

// 6.4 For standard device requests that require no Data stage, a device must
// be able to complete the request and be able to successfully complete
// the Status stage of the request within 50 ms of receipt of the request.
// This limitation applies to request to the device, interface, or endpoint.

// For standard device requests that require data stage transfer to the host,
// the device must be able to return the first data packet to the host within
// 500 ms of receipt of the request. For subsequent data packets, if any,
// the device must be able to return them within 500 ms of successful completion
// of the transmission of the previous packet.

// The device must then be able to successfully complete the status stage within
// 50 ms after returning the last data packet.

// For standard device requests that require a data stage transfer to the device,
// the 5-second limit applies.

// 7. Request Error
// The device deals with the Request Error by returning a STALL PID in reponse to
// the next Data stage transaction or in the Status stage of the message.
// It is preferred that the STALL PID be returned at the next Data stage transaction,
// as this avoids unnecessary bus activity.


// 9.3 USB Device Requests
// Table 9-2. Format of Setup Data
enum {
	BIT_DEF(BM_REQ_TYPE,7,DIR,HOST2DEV,DEV2HOST),
	// In the case of a control pipe, the request should have the Direction bit
	// set to zero but the device may accept either value of the Direction bit.
	BIT_DEF(WINDEX,7,DIR,OUT,IN),
};
typedef struct {
	#define BM_REQ_TYPE_TYPE_MASK		(0x3UL << 5)
	#define BM_REQ_TYPE_TYPE_VAL(x)		((x) << 5)
	#define BM_REQ_TYPE_TYPE_Standard	0x0
	#define BM_REQ_TYPE_TYPE_Class		0x1
	#define BM_REQ_TYPE_TYPE_Vendor		0x2
	#define BM_REQ_TYPE_TYPE_Reserved	0x3
	#define BM_REQ_TYPE_RCPNT_MASK		(0x1FUL << 0)
	#define BM_REQ_TYPE_RCPNT_VAL		((x) << 0)
	#define BM_REQ_TYPE_RCPNT_Device	0x0
	#define BM_REQ_TYPE_RCPNT_Interface	0x1
	#define BM_REQ_TYPE_RCPNT_Endpoint	0x2
	#define BM_REQ_TYPE_RCPNT_Other		0x3
	uint8_t bmRequestType;
	uint8_t	bRequest;
	uint16_t wValue;			// specific to the request
	// When an interface or endpoint is specified, the wIndex field identifies
	// the interface or endpoint.
	#define WINDEX_EP_MASK			(0xFUL << 0)
	#define WINDEX_IF_MASK			(0xFFUL << 0)
	uint16_t wIndex;			// specific to the request
	// If this field is zero, there is no data transfer phase.
	// On an input request, a device must never return more data than is
	// indicated by the WLength Value; it may return less.
	// On an output request, wLength will always indicate the exact amount of
	// data to be sent by the host.
	// Device behavior is undefined if the host should send more data than
	// is specified in wLength.
	uint16_t wLength;			// length of the data
} usb_device_request_t;


// 9.4 Standard Device Requests

// Table 9-4. Standard Request Codes
enum {
	STD_REQ_GET_STATUS,
	STD_REQ_CLEAR_FEATURE,
	STD_REQ_Reserved_2,
	STD_REQ_SET_FEATURE,
	STD_REQ_Reserved_4,
	STD_REQ_SET_ADDRESS,
	STD_REQ_GET_DESCRIPTOR,
	STD_REQ_SET_DESCRIPTOR,
	STD_REQ_GET_CONFIGURATION,
	STD_REQ_SET_CONFIGURATION,
	STD_REQ_GET_INTERFACE,
	STD_REQ_SET_INTERFACE,
	STD_REQ_SYNC_FRAME,
};

// Table 9-5. Descriptor Types
enum {
	DESC_TYPE_DEVICE	= 0x1,
	DESC_TYPE_CONFIGURATION,
	DESC_TYPE_STRING,
	DESC_TYPE_INTERFACE,
	DESC_TYPE_ENDPOINT,
};

// Table 9-6. Standard Feature Selectors
enum {
	STD_FEAT_DEVICE_REMOTE_WAKEUP	= 0x1,
	STD_FEAT_ENDPOINT_HALT		= 0x0,
};

// If an unsupported or invalid request is made to a USB device,
// the device responds by returning STALL in the Data or Status stage of request.
// If the device detects the error in the Setup stage, it is preferred that
// the device return STALL at the earlier of the Data or Status stage.
// Recept of an unsupported or invalid request does NOT cause the optional Halt
// feature on the control pipe to be set.
// If for any reason, the device becomes unable to communicate via its Default
// Control Pipe due to an error condition, the device must be reset to clear
// the conditin and restart the Default Control Pipe.

#endif//__9_USB_DEVICE_FRAMEWORK_H__
