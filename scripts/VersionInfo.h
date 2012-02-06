/*
 *      Author:	Copyright (c) 2005-2012 Marek Sienczak
 *
 *        Desc:	This file contains the version number information
 *				For more details about this Add-in see the website at http://imarqs.com
 *				For any questions or comments, please send an email to support@imarqs.com
 *
 *     Version:	1.02 (created by Add-in version 1.10.11.620 for Visual Studio 2010)
 *
 *        File:	VersionInfo.h
 *     Project:	Lisa50
 */

// Use this constant to enable or disable building the version number of this project.
#define ENABLED 1

// Use this constant to enable or disable building the version number in a debug mode.
#define DEBUG 1

// Project creation date
//   Format: month/day/year
//   Don't modify the format of this value!
#define DATE "2/6/2012"
//   The date in your regional settings is: 2/6/2012

// Version number template
//   A.B.*   = A.B.X.Y
//   A.B.*.* = A.B.X.Z
//   A.B.C.* = A.B.C.Z
//   A.B.C.D = A.B.C.D
//     where the X equals to the number of days since the creation day. If the creation
//     date has not been defined or it's commented, the X equals to the number of days
//     since January 1, 2001 local time. The Y equals to the number of seconds since
//     midnight local time, divided evenly by 10. The Z equals to the incremented build
//     number and the letters A, B, C, D indicate that they remain unchanged.
#define TEMPLATE "1.0.*"

// Use this constant to display the version number.
#define VERSION TEXT("1.0.0.0")

// Don't remove the line below. This number is incrementing by building process.
#define BUILD 0

