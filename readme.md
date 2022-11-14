# Goal of the fork
## Command line interface to decode and encode EXI data

e.g. `$ ./OpenV2G.exe DH8000dbab9371d3234b71d1b981899189d191818991d26b9b3a232b30020000040040` should *D*ecode the Application*H*andshakeRequest.
e.g. `$ ./OpenV2G.exe  EDi_380_20` should *E*ecode with *D*IN schema the CurrentDemandResponse with 380V and 20A

The result is provided on stdout in JSON format, e.g. 
```
	$ ./OpenV2G.exe DD809a001150400000c80006400000
	{
	"msgName": "PreChargeReq",
	"info": "14 bytes to convert",
	"error": "",
	"result": "",
	"schema": "DIN",
	"g_errn": "0",
	"header.SessionID": "",
	"header.Notification_isUsed": "0",
	"header.Signature_isUsed": "0",
	"DC_EVStatus.EVReady": "0",
	"DC_EVStatus.EVErrorCode": "0",
	"DC_EVStatus.EVRESSSOC": "0",
	"EVTargetVoltage.Multiplier": "-1",
	"EVTargetVoltage.Unit": "5",
	"EVTargetVoltage.Value": "3484",
	"EVTargetCurrent.Multiplier": "-1",
	"EVTargetCurrent.Unit": "3",
	"EVTargetCurrent.Value": "10",
	}
```

# Base project
This fork is based on:
https://github.com/Martin-P/OpenV2G
Version 0.9.5, released March 11, 2022

-------------------------------------------------------------------------
OpenV2G - an open source project implementing the basic functionality of the ISO IEC 15118 vehicle to grid (V2G) communication interface 
Version 0.9.5, released March 11, 2022
http://openv2g.sourceforge.net/

Please report bugs via the SourceForge bug tracking system at http://sourceforge.net/tracker/?group_id=350113.
Thank you.

Copyright (C) 2007-2022 Siemens AG

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

