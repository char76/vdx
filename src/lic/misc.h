/*
 * All files in this project are distributed under the GNU General
 * Public License. This is Free Software.
 */
// -------------------------
// misc.h
//
// (C) Dirk Laessig
// -------------------------

#ifndef _MISC_H_
#define _MISC_H_

#include <X11/Intrinsic.h>

// -------------------------------------------------------------------
//
// withSuffix(buffer, len, suffix)
//
// buffer  -  enthaelt einen Dateinamen
// len     -  enthaelt sizeof(buffer)
// suffix  -  suffix (ohne Punkt) wird an buffer gehaengt 
//            enthaelt buffer schon einen Dateinamen mit dem 
//            entsprechenden suffix, so wird suffix nicht angehaengt
// Return:    buffer enthaelt den neuen Dateinamen
//
// Ein suffix wird durch einen Punkt vom Basename getrennt.
// 
// --------------------------------------------------------------------

void withSuffix(char *buffer, unsigned long len, char *suffix);


// -------------------------------------------------------------------
// getSuffix()
// -------------------------------------------------------------------

void getSuffix(char *buffer, char *suffix, unsigned long &len);

// -------------------------------------------------------------------
//
// changeSuffix(buffer, len, suffix)
//
// buffer  -  enthaelt einen Dateinamen
// len     -  enthaelt sizeof(buffer)
// suffix  -  suffix (ohne Punkt) wird an buffer gehaengt 
//            enthaelt buffer schon einen Dateinamen mit einem
//            suffix, so wird suffix ersetzt
// Return:    buffer enthaelt den neuen Dateinamen
//
// Ein suffix wird durch einen Punkt vom Basename getrennt.
// 
// --------------------------------------------------------------------

void changeSuffix(char *buffer, unsigned long len, char *suffix);



// -------------------------------------------------------------------
//
// withoutSuffix(buffer, len, suffix)
//
// buffer  -  enthaelt einen Dateinamen
// Return:    buffer enthaelt den neuen Dateinamen
//
// Der suffix wird abgetrennt
// 
// --------------------------------------------------------------------

void withoutSuffix(char *buffer);


// -------------------------------------------------------------------
//
// getBasename(buffer)
//
// buffer  -  enthaelt einen Dateinamen
// Return:    buffer enthaelt den neuen Dateinamen
//
// Es wird der anfuehrende Pfad entfernt
// 
// --------------------------------------------------------------------

void getBasename(char *buffer);


// -------------------------------------------------------------------
//
// getPath(fullPath,path,len)
//
// fullPath - enthaelt einen Dateinamen, von dem der Pfad
//            extrahiert werden soll
// len      - die Groesse des Buffers, der bei path uebergeben wird
// Return:    path enthaelt den Path mit einem Slash am Ende
//            ist path leer, dann ist das Aktuelle Verzeichnis gemeint
//
// --------------------------------------------------------------------

void getPath(char *fullPath, char *path, unsigned long len);


// -------------------------------------------------------------------
//
// dropSiteFix(Widget)
//
// --------------------------------------------------------------------

void dropSiteFix(Widget,Boolean);

// -------------------------------------------------------------------
//
// replaceForRF()
//
// --------------------------------------------------------------------

void replaceForRF(char *src, char *dest, unsigned long &len);

// -------------------------------------------------------------------
//
// getUserName(char *buf, size_t buffer_size);
//
// --------------------------------------------------------------------

void getUserName(char *buf, size_t &buffer_size);


// -------------------------------------------------------------------
//
// createPath(file)
//
// file - to filename for that the path should be created
// return errno on failure or zero on success
//
// --------------------------------------------------------------------

int createPath(char *file);

#endif /* Don't add stuff after this #endif */
