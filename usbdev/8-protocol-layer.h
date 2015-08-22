// tary, 20:00 2015/8/5
#ifndef __8_PROTOCOL_LAYER_H__
#define __8_PROTOCOL_LAYER_H__

// 8.3.1 Packet Identifier Field
enum {
	PID_OUT		= 0xE1,
	PID_IN		= 0x69,
	PID_SOF		= 0xA5,
	PID_SETUP	= 0x2D,
	PID_DATA0	= 0xC3,
	PID_DATA1	= 0x4B,
	PID_ACK		= 0xD2,
	PID_NAK		= 0x5A,
	PID_STALL	= 0x1E,
	PID_PRE		= 0x3C,
};

// 8.3.2.1 Address Field
// The ADDR field is specified for IN,SETUP,and OUT tokens.
#define ADDR_MASK	0x7FUL
#define ADDR_COUNT	0x80UL

// 8.3.2.2 Endpoint Field
// The endpoint field is defined for IN,SETUP,and OUT token PIDs only.
#define ENDPOINT_MASK	0x0FUL
#define ENDPOINT_COUNT	0x10UL

// 8.3.3 Frame Number Field
#define FRAME_NR_MASK	0x7FFUL
#define FRAME_NR_COUNT	0x800UL

// 8.3.4 Data Field
#define DATA_CNT_MAX	1023

// 8.3.5 Cyclic Redundancy Checks

// 8.4.5 Handshake Responses
// Note that if an error occurs during the transmission of the token
// to the function, the function will not respond with any packets until
// the next token is received and successfully decoded.

// 8.4.5.3 Function Response to an OUT Transaction
// If the data packet was corrupted, the function returns no handshake.

// 8.4.5.4 Function Response to a SETUP Transaction
// A function may not respond to a SETUP token with either STALL or NAK
// and receiving function must accept the data packet that follows
// the SETUP token. If a non-control endpoint receives a SETUP token,
// it must ignore the transaction and return no response.

// 8.5.1 Bulk Transaction
// The data packet transmitter toggles upon receipt of ACK,
// and the receiver toglgles upon receipt and acceptance of a valid 
// data packet.

// 8.5.2.1 Reporting Status Results
// Control write transfers return status information in the data phase
// of the Status stage transaction.
// Control read transfers return status information in the handshake phase
// of a Status stage transaction, after the host has issued a zero-length
// data packet during the previous data phase.
// The function expects the host to repond to the data packet in the
// Status stage with ACK. If the function does not receive ACK, it remains
// in the Status stage of the command and will continue to return the
// zero-length data packet for as long as the host continues to send
// IN tokens.
// If a control pipe returns STALL during the Data stage, there will be
// no Status stage for the control transfer.

// 8.5.2.3 Error Handling on the Last Data Transaction
// If the function did not receive the ACK that ended the Data stage,
// the function will interpret the start of the Status stage as
// verification that the successfully received the data.
// If an ACK handshake on an OUT gets corrupted, the host dones not
// advance to the Status stage and retries the last data instead.

// 8.6.2 Successful Data Transactions
// During each transaction, the receiver compares the transmitter sequence bit
// (encoded in the data packet PID as either DATA0 or DATA1) with its receiver
// sequence bit. If data cannot be accepted, the receiver must issue NAK and
// the sequence bits of both the transmitter and receiver remain unchanged.

// ????????????????????????????????????????????????????????????????????????????
// 8.6.4 Corrupted ACK Handshake
// Consequently, it discards the incoming data packet and does not toggle
// its sequence bit. The receiver then issue ACK, which causes the transmitter
// to regard the retried transaction as successful.
// ????????????????????????????????????????????????????????????????????????????

// 8.7.3 False EOPs
// Detection of false EOP relies upon the fact that a packet into which
// a false EOP has been inserted will apear as a truncated packet with
// a CRC failure.
// When a device sees a corrupted data packet, it issues no response
// and waits for the host send the next token.
// If a device issues a data packet that gets corrupted with a false EOP,
// the host will ignore the packet and not issue the handshake. The device,
// expecting to see a handshake from the host, will timeout.

// If the host receives a corrupted data packet, it assumes that a false EOP
// may have occurred and waits fro 16 bit times to see if there is any
// subsequent upstream traffic.
// If no bus transitions are detected within the 16 bit interval and the bus
// remains in the Idle state, the host may issue the next token.
// Otherwise, the host waits for the device to finish sending the remainder
// of its packet.

#endif//__8_PROTOCOL_LAYER_H__
