#ifndef __SIMPLEHEADER_H
#define __SIMPLEHEADER_H

#include <cstdint>
#define DATA_SZ 512

using namespace std;

struct simplepacket {
  uint8_t Type:2;
  uint8_t TR:1;
  uint8_t Window:5;
  uint8_t seq_Num;
  uint8_t length_msb;
  uint8_t length_lsb;
  uint32_t Timestamp;
  uint16_t crc1_msb;
  uint16_t crc1_lsb;
  char data[DATA_SZ];  // payload
  uint8_t crc2_msb;
  uint8_t crc2_lsb;
};

// class to be tested. Implements a simple packet structure consisting of a 16 bit integer + data
class SimpleHeader {
private:
  struct simplepacket packet;

public:
  // default constructor initializes the header to zero.
  SimpleHeader();

  // sets the 16 bit value of the header
  void setHeader(unsigned int val);

  // returns the header value
  unsigned int getHeader() const;

  // set the type field
  void setType(unsigned int val);


  // return the Type Field
  unsigned int getType() const;


	// set the Window field
  void setWindow(unsigned int val);


  // return the Window Field
  unsigned int getWindow() const;

  // set the TR field
  void setTR(unsigned int val);


  // return the TR Field
  unsigned int getTR() const;

  //set the seqnum
  void setSeqnum(unsigned int val);

  //return the seqnum
  unsigned int getSeqnum() const;

   // set the TR field
  void setTimestamp(unsigned int val);


  // return the TR Field
  unsigned int getTimestamp() const;

 // sets the 16 bit value of the header
  void setCRC1(unsigned int val);

  // returns the header value
  unsigned int getCRC1() const;

  // sets the 16 bit value of the header
   void setCRC2(unsigned int val);

   // returns the header value
   unsigned int getCRC2() const;


  //converts packet to string
  string convertPacketToString();


  // returns the size of the packet, including headers and data
  // to be used with recvfrom() or sendto()
  int packetSize() const {
    return sizeof(simplepacket);
  }

  // returns the size of the payload. Use with reading / writing to/from files
  int payloadSize() const {
    return DATA_SZ;
  }

  // returns pointer to the structure holding the thePacket, including the headers
  // To be used with recvfrom or sendto
  void * thePacket() {
    return &packet;
  }

  void * thePayload() {
    return packet.data;
  }
};

#endif
