#include "err.h"
#include "gfx/gfx.h"
#include "hid/hid.h"
#include "gfx/gfxutils.h"

const char *TEErrors[] = {
    "I/O FEHLER",
    "KEINE DISK",
    "NICHT BEREIT",
    "KEINE DATEI",
    "KEIN PFAD",
    "PFAD UNGUELTIG",
    "ZUGRIFF VERWEIGERT",
    "ZUGRIFF VERWEIGERT",
    "PTR UNGUELTIG",
    "GESCHUETZT",
    "UNGUELTIGES LW",
    "KEIN MEM",
    "KEIN FAT",
    "MKFS ABBRUCH",
    [TE_ERR_UNIMPLEMENTED - 1] = "Nicht implementiert",
    [TE_EXCEPTION_RESET - 1] = "E Zuruecksetzen",
    [TE_EXCEPTION_UNDEFINED - 1] = "E Undefiniert",
    [TE_EXCEPTION_PREF_ABORT - 1] = "E Pref Abbruch",
    [TE_EXCEPTION_DATA_ABORT - 1] = "E Daten Abbruch",
    [TE_ERR_SAME_LOC - 1] = "Gleicher Zielpfad",
    [TE_ERR_KEYDUMP_FAIL - 1] = "Keydump fehlgeschlagen",
    [TE_ERR_PARTITION_NOT_FOUND - 1] = "Partition nicht gefunden",
    [TE_ERR_PATH_IN_PATH - 1] = "Ordner kann nicht in sich selbst verschoben/kopiert werden",
    [TE_ERR_EMMC_READ_FAIL - 1] = "eMMC/emuMMC Lesefehler",
    [TE_ERR_EMMC_WRITE_FAIL - 1] = "eMMC/emuMMC Schreibfehler",
    [TE_ERR_NO_SD - 1] = "Keine SD erkannt",
    [TE_ERR_FILE_TOO_BIG_FOR_DEST - 1] = "Datei zu gross fuer Ziel",
};

const char *GetErrStr(u32 err){
    --err; // obv error codes cannot be 0
    if (err >= 0 && err < ARRAY_SIZE(TEErrors))
        return TEErrors[err];

    return "(Unbekannt)";
}

#define lx 256
#define ly 240
#define lenx 768
#define leny 240

void DrawError(ErrCode_t err){
    if (err.err == 0)
        return;
        
    SETCOLOR(COLOR_ORANGE, COLOR_DARKGREY);
    gfx_box(lx, ly, lx + lenx, ly + leny, COLOR_ORANGE);
    gfx_boxGrey(lx + 16, ly + 16, lx + lenx - 16, ly + leny - 16, 0x33);
    gfx_con_setpos(lx + ((lenx - 17 * 16) / 2), ly + 32);
    gfx_printf("Ein Fehler ist aufgetreten!\n\n%bFehler : %d\nZeile: %d\nDatei: %s\nZiel: %s%b", lx + 48, err.err, err.loc, err.file, GetErrStr(err.err), 0);
    gfx_con_setpos(lx + ((lenx - 19 * 16) / 2), ly + leny - 48);
    gfx_printf("Druecke A zum fortfahren");
    
    hidWaitMask((JoyA | JoyB));
}