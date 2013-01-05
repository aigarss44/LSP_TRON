/* 
 * File:   packets.h
 * Author: FlutterCanon
 *
 * Created on January 5, 2013, 1:12 PM
 * 
 * No Google Grups
 * 
 * Darbîbas apraksts.
Katras paketes pamatâ ir Header struktûra, ar kuru sâkas kaut kâdi dati. Tajâ ir paketes tips un datu garums baitos, kas seko aiz Headera.

Konekcijas nodibinâðana.
Sâkumâ serveris klausâs un klienti sûta PCKT_CONNECTION_REQUEST (lûgumu pievienoties serverim). Ja serverî ir vietas, tad tas sûta atpakaï PCKT_CONNECTION_RESPONSE. Serveris generç unikâlu ID, ko pieðíir lietotâjam, lietotâjs to saglabâ. ID tiks izmantots sûtot servera update.
Kas notiek, ja serverî nav vietu ? Piedâvâju uztaisît jaunu tipu PCKT_CONNECTION_REFUSED vai arî vienkârði aizvçrt konekciju, kas signalizçtu, ka serverî nav vietu.)
Praktiskajos darbos spriedâm par responsa laukiem, îsti nemâcçju paskaidrot, kâpçc mums vajag astes garumu, jo visas astes tâ vai tâ tiks sûtîtas ar Update pakâm un to daudzums bûs daþâds. Lîdzîgi ir arî ar spçlçtâju daudzumu.
Kâpçc mums bija vajadzîgs timeout lauks ?

Update par spçles progresu.
Kad maksimâlais spçlçtâju skaits ir sasniegts, sâkas spçle. Tiek izsûtîts pirmais PCKT_UPDATE, tas iekïauj visu informâciju par spçles laukumu. No update arî iegûstam savas sâkuma koordinâtes. No gameover laukiem nosakam uzvarçtâju.
Update ielasîðanas algoritms:
Ielasam UpdatePlayerHeader, ielasam UpdatePlayer * UpdatePlayerHeader.playerCount.
Analoìiski ar lodçm.
Lîdzîgi ar astçm, tikai vispirms UpdateTotalTailHeader, tad ielasam pirmo UpdateTailHeader, kam uzreiz seko UpdateTail * UpdateTailHeader.tailCount struktûras. Pçc tam ielasam nâkamo UpdateTailHeader.
Domâju ðis ir labs un viegls veids kâ veidot updeitus. Atceros, ka izskançja runas par tukðâm vçrtîbâm un konstantu skaitu vismaz spçlçtâju updeitiem, bet vai tâ bûs vieglâk ?

Spçlçtâja notikumi.
Spçlçtâjs ik pa laikam (framerate reizes sekundç) sûta savus notikumus ar EventPlayer struktûru. Cik saprotu, tad ðo paku varam nesûtît, ja neko nederam - kustamies uz priekðu. Serverim jârûpçjas, lai spçlçtâji kustçtos tikai pa framiem un nepieòemtu EventPlayer pakas, kad nav jauns frame vai spçlçtâjs ir miris.
Vienâ reizç varam pakustçties pa labi, kreisi, uz priekðu un izðaut. Darbîbu secîba ir vispirms pagrieþamies un tad ðaujam. Direction laukâ vajag bût vçrtîbâm MOVE_RIGHT, MOVE_LEFT, MOVE_FORWARD.

Citas Lietas.
Visi vairâku baitu struktûru lauki (uint32_t...) ir network endianâ. Tâtâd pirms sûtam datus ârâ katru ðâdu lauku apstrâdâjam ar htonl vai htons (Host to network). Visus ienâkoðos laukus atkal apstrâdâjam ar ntohs vai ntohl (Network to host).
Mûsu gadîjumâ sanâk izmantot tikai htonl un ntohl.

Vajag precizçt.
Vai pareizi atceros, ka mçs varam ðaut tikai vienu lodi ik pa N kadriem ? Atceros, ka bija kaut kâdas runas par loþu daudzumu.
Metaserveris. Vai nevajag kaut kâdu veidu kâ noskaidrot serverus tîklâ.
Citi jautâjumi ?
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
    uint32_t length;           // Tâlâkâ satura garums (baitos)
} __attribute__((packed));

/* Klienta - servera konekcijas nodibinâðana */

struct ConnectionRequest {
    /* Tukðums - Header.length = 0 */
} __attribute__((packed));

struct ConnectionResponse {
    uint32_t id;               // Izsniegtais ID
    uint32_t height;           // Spçles laukuma augstums >= 30
    uint32_t width;            // Spçles laukuma platums >= 80
    uint32_t playerCount;      // Spçlçtâju daudzums (vajadzîgs ?)
    uint32_t tailLength;       // Astes garums (vajadzîgs ?)
    uint32_t frameRate;        // Kadri sekundç
    uint32_t bulletSpeed;      // Lodes âtrums (kadros)
    uint32_t bulletCooldown;   // Lodes cooldowns (kadros)
    uint32_t timeout;          // ??
} __attribute__((packed));

/* Servera updeiti */

struct UpdatePlayerHeader {
    uint32_t playerCount;      // Cik UpdatePlayer struktûras sekos
} __attribute__((packed));

struct UpdatePlayer {
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t direction;        // DIR_*
    uint32_t cooldown;         // Lodes cooldown (Kadros)
    uint32_t gameover;         // 1 - miris, 0 - spçlç
} __attribute__((packed));

struct UpdateBulletHeader {
    uint32_t bulletCount;      // Cik UpdateBullet struktûras sekos
} __attribute__((packed));

struct UpdateBullet {
    uint32_t id;
    uint32_t x;
    uint32_t y;
    uint32_t direction;        // DIR_*
} __attribute__((packed));

struct UpdateTotalTailHeader {
    uint32_t totalTailLength;  // Cik UpdateTailHeader struktûras sekos
} __attribute__((packed));

struct UpdateTailHeader {
    uint32_t id;
    uint32_t tailCount;        // Cik UpdateTail struktûras sekos
} __attribute__((packed));

struct UpdateTail {
    uint32_t x;
    uint32_t y;
} __attribute__((packed));

/* Klienta notikumi */

struct EventPlayer {
    uint8_t direction;         // MOVE_*
    uint8_t shot;              // 1 - izðauj, 0 - neðauj
} __attribute__((packed));