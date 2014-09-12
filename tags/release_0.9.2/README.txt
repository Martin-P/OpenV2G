-------------------------------------------------------------------------
OpenV2G - an open source project implementing the basic functionality of the ISO IEC 15118 vehicle to grid (V2G) communication interface 
Version 0.9.2, released September 12, 2014
http://openv2g.sourceforge.net/

Please report bugs via the SourceForge bug tracking system at http://sourceforge.net/tracker/?group_id=350113.
Thank you.

Copyright (C) 2007-2014 Siemens AG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

-------------------------------------------------------------------------
CHANGES from version 0.9.1:
-------------------------------------------------------------------------
* resolves bug with name clashes w.r.t. iso and din track
* fixes issue with test code for init handshake 
* Note: OpenV2G 0.9.2 is essentially just a bug fixed version of OpenV2G 0.9.1

-------------------------------------------------------------------------
CHANGES from version 0.9:
-------------------------------------------------------------------------
* includes support for DIN and hence interoperability with OpenV2G 0.7
  (needs to be switched on though by #define DEPLOY_DIN_CODEC)
* fixes bugs and warnings for Visual Studio
* Note: OpenV2G 0.9.1 is a superset of previous versions
  v2g...c/h files support ISO track
  din...c/h files support DIN track

-------------------------------------------------------------------------
CHANGES from version 0.8:
-------------------------------------------------------------------------
* large code footprint reduction which resulted in a new API
  (please take a look at the example in src/test folder)
* datatype differences w.r.t. arrays, strings, bytes, isUsed, and enum-naming
* bug-fixes
* Note: OpenV2G 0.8 and 0.9 are interoperable, meaning that one can generate
  streams with one and decode with the other or vice-versa

-------------------------------------------------------------------------
CHANGES from version 0.7:
-------------------------------------------------------------------------
* adaption of V2G schema changes (reflects the ISO/IEC 15118-2 FDIS status)
* bug-fixes


-------------------------------------------------------------------------
CHANGES from version 0.7:
-------------------------------------------------------------------------
* adaption of V2G schema changes (reflects the ISO/IEC 15118-2 FDIS status)
* bug-fixes

-------------------------------------------------------------------------
CHANGES from version 0.6:
-------------------------------------------------------------------------
* adaption of V2G schema changes (reflects the ISO/IEC 15118-2 DIS status and DIN 70121)
* reduced memory usage
* EXI decoder skips schema deviations according to EXI Profile
* bug-fixes

-------------------------------------------------------------------------
CHANGES from version 0.5:
-------------------------------------------------------------------------
* adaption of V2G schema changes
* application handshake protocol implementation 
* asynchronised communication
* reduced memory usage
* changed V2GTP byte order from little endian to big endian
* bug-fixes
* updated AC demo interaction between EV and EVSE, and
* updated DC demo interaction between EV and EVSE


-------------------------------------------------------------------------
CHANGES from version 0.4:
-------------------------------------------------------------------------
* adaption of V2G schema changes
* V2GTP implementation (replaces the DoIP implementation)
* EXI default coder for the 15118 schema (replaces the strict mode of EXI)
* AC demo interaction between PEV and EVSE, and
* DC demo interaction between PEV and EVSE


-------------------------------------------------------------------------
CHANGES from version 0.3.1:
-------------------------------------------------------------------------
* adaption of V2G schema changes
* supporting of DC messages
* example program showing the message sequence of AC charging and 
DC charging
* bug-fixes

-------------------------------------------------------------------------
CHANGES from version 0.3:
-------------------------------------------------------------------------
* Bug-fixes
* reduced memory usage
* some type changes in the EXI codec and V2G service: 
** struct v2gService->struct EXIService in v2g_service.h
** size_t->uint16_t in v2g_serviceClientDataTransmitter.h and doIP.h
* renaming of some enumeration values in v2g_serviceDataTypes.h

-------------------------------------------------------------------------
CHANGES from version 0.2.2:
-------------------------------------------------------------------------
* Bug-fixes
* first DoIP implementation
* V2G message error handling
* adaption of V2G schema changes
* code optimizations

-------------------------------------------------------------------------
CHANGES from version 0.2.1:
-------------------------------------------------------------------------
* Bug-fixes
* adaption of V2G schema changes
* some code optimizations

-------------------------------------------------------------------------
CHANGES from version 0.2:
-------------------------------------------------------------------------
* Bug-fixes
* Fixed compiler warnings

-------------------------------------------------------------------------
CHANGES from version 0.1:
-------------------------------------------------------------------------
* Bug-fixes
* Service and Client added