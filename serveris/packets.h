/* 
 * File:   packets.h
 * Author: FlutterCanon
 *
 * Created on January 5, 2013, 1:12 PM
 * 
 * No Google Grups
 * 
 * Darb�bas apraksts.
Katras paketes pamat� ir Header strukt�ra, ar kuru s�kas kaut k�di dati. Taj� ir paketes tips un datu garums baitos, kas seko aiz Headera.

Konekcijas nodibin��ana.
S�kum� serveris klaus�s un klienti s�ta PCKT_CONNECTION_REQUEST (l�gumu pievienoties serverim). Ja server� ir vietas, tad tas s�ta atpaka� PCKT_CONNECTION_RESPONSE. Serveris gener� unik�lu ID, ko pie��ir lietot�jam, lietot�js to saglab�. ID tiks izmantots s�tot servera update.
Kas notiek, ja server� nav vietu ? Pied�v�ju uztais�t jaunu tipu PCKT_CONNECTION_REFUSED vai ar� vienk�r�i aizv�rt konekciju, kas signaliz�tu, ka server� nav vietu.)
Praktiskajos darbos spried�m par responsa laukiem, �sti nem�c�ju paskaidrot, k�p�c mums vajag astes garumu, jo visas astes t� vai t� tiks s�t�tas ar Update pak�m un to daudzums b�s da��ds. L�dz�gi ir ar� ar sp�l�t�ju daudzumu.
K�p�c mums bija vajadz�gs timeout lauks ?

Update par sp�les progresu.
Kad maksim�lais sp�l�t�ju skaits ir sasniegts, s�kas sp�le. Tiek izs�t�ts pirmais PCKT_UPDATE, tas iek�auj visu inform�ciju par sp�les laukumu. No update ar� ieg�stam savas s�kuma koordin�tes. No gameover laukiem nosakam uzvar�t�ju.
Update ielas��anas algoritms:
Ielasam UpdatePlayerHeader, ielasam UpdatePlayer * UpdatePlayerHeader.playerCount.
Analo�iski ar lod�m.
L�dz�gi ar ast�m, tikai vispirms UpdateTotalTailHeader, tad ielasam pirmo UpdateTailHeader, kam uzreiz seko UpdateTail * UpdateTailHeader.tailCount strukt�ras. P�c tam ielasam n�kamo UpdateTailHeader.
Dom�ju �is ir labs un viegls veids k� veidot updeitus. Atceros, ka izskan�ja runas par tuk��m v�rt�b�m un konstantu skaitu vismaz sp�l�t�ju updeitiem, bet vai t� b�s viegl�k ?

Sp�l�t�ja notikumi.
Sp�l�t�js ik pa laikam (framerate reizes sekund�) s�ta savus notikumus ar EventPlayer strukt�ru. Cik saprotu, tad �o paku varam nes�t�t, ja neko nederam - kustamies uz priek�u. Serverim j�r�p�jas, lai sp�l�t�ji kust�tos tikai pa framiem un nepie�emtu EventPlayer pakas, kad nav jauns frame vai sp�l�t�js ir miris.
Vien� reiz� varam pakust�ties pa labi, kreisi, uz priek�u un iz�aut. Darb�bu sec�ba ir vispirms pagrie�amies un tad �aujam. Direction lauk� vajag b�t v�rt�b�m MOVE_RIGHT, MOVE_LEFT, MOVE_FORWARD.

Citas Lietas.
Visi vair�ku baitu strukt�ru lauki (uint32_t...) ir network endian�. T�t�d pirms s�tam datus �r� katru ��du lauku apstr�d�jam ar htonl vai htons (Host to network). Visus ien�ko�os laukus atkal apstr�d�jam ar ntohs vai ntohl (Network to host).
M�su gad�jum� san�k izmantot tikai htonl un ntohl.

Vajag preciz�t.
Vai pareizi atceros, ka m�s varam �aut tikai vienu lodi ik pa N kadriem ? Atceros, ka bija kaut k�das runas par lo�u daudzumu.
Metaserveris. Vai nevajag kaut k�du veidu k� noskaidrot serverus t�kl�.
Citi jaut�jumi ?
Ko es esmu aizmirsis ?

-Roberts
 */

#include <stdarg.h>

const uint32_t DIR_RIGHT    = 0;
const uint32_t DIR_UP       = 1;
const uint32_t DIR_LEFT     = 2;
const uint32_t DIR_DOWN     = 3;

const uint32_t MOVE_RIGHT   = 0;
const uint32_t MOVE_LEFT    = 1;
const uint32_t MOVE_FORWARD = 2;

const uint32_t PCKT_CONNECTION_REQUEST  = 1;
const uint32_t PCKT_CONNECTION_RESPONSE = 2;
const uint32_t PCKT_UPDATE              = 3;
const uint32_t PCKT_EVENT               = 4;

struct Header {
    uint8_t type;              // PCKT_*
    uint32_t length;           // T�l�k� satura garums (baitos)
} __attribute__((packed));

/* Klienta - servera konekcijas nodibin��ana */

struct ConnectionRequest {
    /* Tuk�ums - Header.length = 0 */
} __attribute__((packed));

struct ConnectionResponse {
    uint32_t id;               // Izsniegtais ID
    uint32_t height;           // Sp�les laukuma augstums >= 30
    uint32_t width;            // Sp�les laukuma platums >= 80
    uint32_t playerCount;      // Sp�l�t�ju daudzums (vajadz�gs ?)
    uint32_t tailLength;       // Astes garums (vajadz�gs ?)
    uint32_t frameRate;        // Kadri sekund�
    uint32_t bulletSpeed;      // Lodes �trums (kadros)
    uint32_t bulletCooldown;   // Lodes cooldowns (kadros)
    uint32_t timeout;          // ??
} __attribute__((packed));

/* Servera updeiti */

struct UpdatePlayerHeader {
    uint32_t playerCount;      // Cik UpdatePlayer strukt�ras sekos
} __attribute__((packed));

struct UpdatePlayer {
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t direction;        // DIR_*
    uint32_t cooldown;         // Lodes cooldown (Kadros)
    uint32_t gameover;         // 1 - miris, 0 - sp�l�
} __attribute__((packed));

struct UpdateBulletHeader {
    uint32_t bulletCount;      // Cik UpdateBullet strukt�ras sekos
} __attribute__((packed));

struct UpdateBullet {
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t direction;        // DIR_*
} __attribute__((packed));

struct UpdateTotalTailHeader {
    uint32_t totalTailLength;  // Cik UpdateTailHeader strukt�ras sekos
} __attribute__((packed));

struct UpdateTailHeader {
    uint32_t id;
    uint32_t tailCount;        // Cik UpdateTail strukt�ras sekos
} __attribute__((packed));

struct UpdateTail {
    uint32_t x;
    uint32_t y;
} __attribute__((packed));

/* Klienta notikumi */

struct EventPlayer {
    uint8_t direction;         // MOVE_*
    uint8_t shot;              // 1 - iz�auj, 0 - ne�auj
} __attribute__((packed));