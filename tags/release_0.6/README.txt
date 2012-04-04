-------------------------------------------------------------------------
OpenV2G - an open source project implementing the basic functionality of the ISO IEC 15118 vehicle to grid (V2G) communication interface 
Version 0.6, released April 2, 2012
http://openv2g.sourceforge.net/

Please report bugs via the SourceForge bug tracking system at http://sourceforge.net/tracker/?group_id=350113.
Thank you.


Copyright (C) 2007-2012 Siemens AG

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