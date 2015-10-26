// tary, 22:13 2015/10/26
#ifndef __9_USB_DEVICE_FRAMEWORK_H__
#define __9_USB_DEVICE_FRAMEWORK_H__

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


	// 9.1.16 Suspended
	// ???
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

#endif//__9_USB_DEVICE_FRAMEWORK_H__
