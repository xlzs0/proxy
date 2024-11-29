#include <cstdint>
#include <vcruntime_string.h>
#include <utility>

inline const uint32_t mask_table[33] = {
	0,
	(1 << 1) - 1,
	(1 << 2) - 1,
	(1 << 3) - 1,
	(1 << 4) - 1,
	(1 << 5) - 1,
	(1 << 6) - 1,
	(1 << 7) - 1,
	(1 << 8) - 1,
	(1 << 9) - 1,
	(1 << 10) - 1,
	(1 << 11) - 1,
	(1 << 12) - 1,
	(1 << 13) - 1,
	(1 << 14) - 1,
	(1 << 15) - 1,
	(1 << 16) - 1,
	(1 << 17) - 1,
	(1 << 18) - 1,
	(1 << 19) - 1,
	(1 << 20) - 1,
	(1 << 21) - 1,
	(1 << 22) - 1,
	(1 << 23) - 1,
	(1 << 24) - 1,
	(1 << 25) - 1,
	(1 << 26) - 1,
	(1 << 27) - 1,
	(1 << 28) - 1,
	(1 << 29) - 1,
	(1 << 30) - 1,
	0x7FFFFFFF,
	0xFFFFFFFF,
};

inline const uint32_t bit_write_mask[32][33] = {
	{ 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0, 0xFFFFFF80, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000, 0xFFFFE000, 0xFFFFC000, 0xFFFF8000, 0xFFFF0000, 0xFFFE0000, 0xFFFC0000, 0xFFF80000, 0xFFF00000, 0xFFE00000, 0xFFC00000, 0xFF800000, 0xFF000000, 0xFE000000, 0xFC000000, 0xF8000000, 0xF0000000, 0xE0000000, 0xC0000000, 0x80000000, 0x00000000 },
	{ 0xFFFFFFFF, 0xFFFFFFFD, 0xFFFFFFF9, 0xFFFFFFF1, 0xFFFFFFE1, 0xFFFFFFC1, 0xFFFFFF81, 0xFFFFFF01, 0xFFFFFE01, 0xFFFFFC01, 0xFFFFF801, 0xFFFFF001, 0xFFFFE001, 0xFFFFC001, 0xFFFF8001, 0xFFFF0001, 0xFFFE0001, 0xFFFC0001, 0xFFF80001, 0xFFF00001, 0xFFE00001, 0xFFC00001, 0xFF800001, 0xFF000001, 0xFE000001, 0xFC000001, 0xF8000001, 0xF0000001, 0xE0000001, 0xC0000001, 0x80000001, 0x00000001, 0x00000001 },
	{ 0xFFFFFFFF, 0xFFFFFFFB, 0xFFFFFFF3, 0xFFFFFFE3, 0xFFFFFFC3, 0xFFFFFF83, 0xFFFFFF03, 0xFFFFFE03, 0xFFFFFC03, 0xFFFFF803, 0xFFFFF003, 0xFFFFE003, 0xFFFFC003, 0xFFFF8003, 0xFFFF0003, 0xFFFE0003, 0xFFFC0003, 0xFFF80003, 0xFFF00003, 0xFFE00003, 0xFFC00003, 0xFF800003, 0xFF000003, 0xFE000003, 0xFC000003, 0xF8000003, 0xF0000003, 0xE0000003, 0xC0000003, 0x80000003, 0x00000003, 0x00000003, 0x00000003 },
	{ 0xFFFFFFFF, 0xFFFFFFF7, 0xFFFFFFE7, 0xFFFFFFC7, 0xFFFFFF87, 0xFFFFFF07, 0xFFFFFE07, 0xFFFFFC07, 0xFFFFF807, 0xFFFFF007, 0xFFFFE007, 0xFFFFC007, 0xFFFF8007, 0xFFFF0007, 0xFFFE0007, 0xFFFC0007, 0xFFF80007, 0xFFF00007, 0xFFE00007, 0xFFC00007, 0xFF800007, 0xFF000007, 0xFE000007, 0xFC000007, 0xF8000007, 0xF0000007, 0xE0000007, 0xC0000007, 0x80000007, 0x00000007, 0x00000007, 0x00000007, 0x00000007 },
	{ 0xFFFFFFFF, 0xFFFFFFEF, 0xFFFFFFCF, 0xFFFFFF8F, 0xFFFFFF0F, 0xFFFFFE0F, 0xFFFFFC0F, 0xFFFFF80F, 0xFFFFF00F, 0xFFFFE00F, 0xFFFFC00F, 0xFFFF800F, 0xFFFF000F, 0xFFFE000F, 0xFFFC000F, 0xFFF8000F, 0xFFF0000F, 0xFFE0000F, 0xFFC0000F, 0xFF80000F, 0xFF00000F, 0xFE00000F, 0xFC00000F, 0xF800000F, 0xF000000F, 0xE000000F, 0xC000000F, 0x8000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F },
	{ 0xFFFFFFFF, 0xFFFFFFDF, 0xFFFFFF9F, 0xFFFFFF1F, 0xFFFFFE1F, 0xFFFFFC1F, 0xFFFFF81F, 0xFFFFF01F, 0xFFFFE01F, 0xFFFFC01F, 0xFFFF801F, 0xFFFF001F, 0xFFFE001F, 0xFFFC001F, 0xFFF8001F, 0xFFF0001F, 0xFFE0001F, 0xFFC0001F, 0xFF80001F, 0xFF00001F, 0xFE00001F, 0xFC00001F, 0xF800001F, 0xF000001F, 0xE000001F, 0xC000001F, 0x8000001F, 0x0000001F, 0x0000001F, 0x0000001F, 0x0000001F, 0x0000001F, 0x0000001F },
	{ 0xFFFFFFFF, 0xFFFFFFBF, 0xFFFFFF3F, 0xFFFFFE3F, 0xFFFFFC3F, 0xFFFFF83F, 0xFFFFF03F, 0xFFFFE03F, 0xFFFFC03F, 0xFFFF803F, 0xFFFF003F, 0xFFFE003F, 0xFFFC003F, 0xFFF8003F, 0xFFF0003F, 0xFFE0003F, 0xFFC0003F, 0xFF80003F, 0xFF00003F, 0xFE00003F, 0xFC00003F, 0xF800003F, 0xF000003F, 0xE000003F, 0xC000003F, 0x8000003F, 0x0000003F, 0x0000003F, 0x0000003F, 0x0000003F, 0x0000003F, 0x0000003F, 0x0000003F },
	{ 0xFFFFFFFF, 0xFFFFFF7F, 0xFFFFFE7F, 0xFFFFFC7F, 0xFFFFF87F, 0xFFFFF07F, 0xFFFFE07F, 0xFFFFC07F, 0xFFFF807F, 0xFFFF007F, 0xFFFE007F, 0xFFFC007F, 0xFFF8007F, 0xFFF0007F, 0xFFE0007F, 0xFFC0007F, 0xFF80007F, 0xFF00007F, 0xFE00007F, 0xFC00007F, 0xF800007F, 0xF000007F, 0xE000007F, 0xC000007F, 0x8000007F, 0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F, 0x0000007F },
	{ 0xFFFFFFFF, 0xFFFFFEFF, 0xFFFFFCFF, 0xFFFFF8FF, 0xFFFFF0FF, 0xFFFFE0FF, 0xFFFFC0FF, 0xFFFF80FF, 0xFFFF00FF, 0xFFFE00FF, 0xFFFC00FF, 0xFFF800FF, 0xFFF000FF, 0xFFE000FF, 0xFFC000FF, 0xFF8000FF, 0xFF0000FF, 0xFE0000FF, 0xFC0000FF, 0xF80000FF, 0xF00000FF, 0xE00000FF, 0xC00000FF, 0x800000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF },
	{ 0xFFFFFFFF, 0xFFFFFDFF, 0xFFFFF9FF, 0xFFFFF1FF, 0xFFFFE1FF, 0xFFFFC1FF, 0xFFFF81FF, 0xFFFF01FF, 0xFFFE01FF, 0xFFFC01FF, 0xFFF801FF, 0xFFF001FF, 0xFFE001FF, 0xFFC001FF, 0xFF8001FF, 0xFF0001FF, 0xFE0001FF, 0xFC0001FF, 0xF80001FF, 0xF00001FF, 0xE00001FF, 0xC00001FF, 0x800001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF, 0x000001FF },
	{ 0xFFFFFFFF, 0xFFFFFBFF, 0xFFFFF3FF, 0xFFFFE3FF, 0xFFFFC3FF, 0xFFFF83FF, 0xFFFF03FF, 0xFFFE03FF, 0xFFFC03FF, 0xFFF803FF, 0xFFF003FF, 0xFFE003FF, 0xFFC003FF, 0xFF8003FF, 0xFF0003FF, 0xFE0003FF, 0xFC0003FF, 0xF80003FF, 0xF00003FF, 0xE00003FF, 0xC00003FF, 0x800003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF },
	{ 0xFFFFFFFF, 0xFFFFF7FF, 0xFFFFE7FF, 0xFFFFC7FF, 0xFFFF87FF, 0xFFFF07FF, 0xFFFE07FF, 0xFFFC07FF, 0xFFF807FF, 0xFFF007FF, 0xFFE007FF, 0xFFC007FF, 0xFF8007FF, 0xFF0007FF, 0xFE0007FF, 0xFC0007FF, 0xF80007FF, 0xF00007FF, 0xE00007FF, 0xC00007FF, 0x800007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF },
	{ 0xFFFFFFFF, 0xFFFFEFFF, 0xFFFFCFFF, 0xFFFF8FFF, 0xFFFF0FFF, 0xFFFE0FFF, 0xFFFC0FFF, 0xFFF80FFF, 0xFFF00FFF, 0xFFE00FFF, 0xFFC00FFF, 0xFF800FFF, 0xFF000FFF, 0xFE000FFF, 0xFC000FFF, 0xF8000FFF, 0xF0000FFF, 0xE0000FFF, 0xC0000FFF, 0x80000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF },
	{ 0xFFFFFFFF, 0xFFFFDFFF, 0xFFFF9FFF, 0xFFFF1FFF, 0xFFFE1FFF, 0xFFFC1FFF, 0xFFF81FFF, 0xFFF01FFF, 0xFFE01FFF, 0xFFC01FFF, 0xFF801FFF, 0xFF001FFF, 0xFE001FFF, 0xFC001FFF, 0xF8001FFF, 0xF0001FFF, 0xE0001FFF, 0xC0001FFF, 0x80001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF, 0x00001FFF },
	{ 0xFFFFFFFF, 0xFFFFBFFF, 0xFFFF3FFF, 0xFFFE3FFF, 0xFFFC3FFF, 0xFFF83FFF, 0xFFF03FFF, 0xFFE03FFF, 0xFFC03FFF, 0xFF803FFF, 0xFF003FFF, 0xFE003FFF, 0xFC003FFF, 0xF8003FFF, 0xF0003FFF, 0xE0003FFF, 0xC0003FFF, 0x80003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF, 0x00003FFF },
	{ 0xFFFFFFFF, 0xFFFF7FFF, 0xFFFE7FFF, 0xFFFC7FFF, 0xFFF87FFF, 0xFFF07FFF, 0xFFE07FFF, 0xFFC07FFF, 0xFF807FFF, 0xFF007FFF, 0xFE007FFF, 0xFC007FFF, 0xF8007FFF, 0xF0007FFF, 0xE0007FFF, 0xC0007FFF, 0x80007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF },
	{ 0xFFFFFFFF, 0xFFFEFFFF, 0xFFFCFFFF, 0xFFF8FFFF, 0xFFF0FFFF, 0xFFE0FFFF, 0xFFC0FFFF, 0xFF80FFFF, 0xFF00FFFF, 0xFE00FFFF, 0xFC00FFFF, 0xF800FFFF, 0xF000FFFF, 0xE000FFFF, 0xC000FFFF, 0x8000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF },
	{ 0xFFFFFFFF, 0xFFFDFFFF, 0xFFF9FFFF, 0xFFF1FFFF, 0xFFE1FFFF, 0xFFC1FFFF, 0xFF81FFFF, 0xFF01FFFF, 0xFE01FFFF, 0xFC01FFFF, 0xF801FFFF, 0xF001FFFF, 0xE001FFFF, 0xC001FFFF, 0x8001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF, 0x0001FFFF },
	{ 0xFFFFFFFF, 0xFFFBFFFF, 0xFFF3FFFF, 0xFFE3FFFF, 0xFFC3FFFF, 0xFF83FFFF, 0xFF03FFFF, 0xFE03FFFF, 0xFC03FFFF, 0xF803FFFF, 0xF003FFFF, 0xE003FFFF, 0xC003FFFF, 0x8003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF },
	{ 0xFFFFFFFF, 0xFFF7FFFF, 0xFFE7FFFF, 0xFFC7FFFF, 0xFF87FFFF, 0xFF07FFFF, 0xFE07FFFF, 0xFC07FFFF, 0xF807FFFF, 0xF007FFFF, 0xE007FFFF, 0xC007FFFF, 0x8007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF, 0x0007FFFF },
	{ 0xFFFFFFFF, 0xFFEFFFFF, 0xFFCFFFFF, 0xFF8FFFFF, 0xFF0FFFFF, 0xFE0FFFFF, 0xFC0FFFFF, 0xF80FFFFF, 0xF00FFFFF, 0xE00FFFFF, 0xC00FFFFF, 0x800FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF, 0x000FFFFF },
	{ 0xFFFFFFFF, 0xFFDFFFFF, 0xFF9FFFFF, 0xFF1FFFFF, 0xFE1FFFFF, 0xFC1FFFFF, 0xF81FFFFF, 0xF01FFFFF, 0xE01FFFFF, 0xC01FFFFF, 0x801FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF, 0x001FFFFF },
	{ 0xFFFFFFFF, 0xFFBFFFFF, 0xFF3FFFFF, 0xFE3FFFFF, 0xFC3FFFFF, 0xF83FFFFF, 0xF03FFFFF, 0xE03FFFFF, 0xC03FFFFF, 0x803FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF, 0x003FFFFF },
	{ 0xFFFFFFFF, 0xFF7FFFFF, 0xFE7FFFFF, 0xFC7FFFFF, 0xF87FFFFF, 0xF07FFFFF, 0xE07FFFFF, 0xC07FFFFF, 0x807FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF },
	{ 0xFFFFFFFF, 0xFEFFFFFF, 0xFCFFFFFF, 0xF8FFFFFF, 0xF0FFFFFF, 0xE0FFFFFF, 0xC0FFFFFF, 0x80FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF },
	{ 0xFFFFFFFF, 0xFDFFFFFF, 0xF9FFFFFF, 0xF1FFFFFF, 0xE1FFFFFF, 0xC1FFFFFF, 0x81FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF, 0x01FFFFFF },
	{ 0xFFFFFFFF, 0xFBFFFFFF, 0xF3FFFFFF, 0xE3FFFFFF, 0xC3FFFFFF, 0x83FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF, 0x03FFFFFF },
	{ 0xFFFFFFFF, 0xF7FFFFFF, 0xE7FFFFFF, 0xC7FFFFFF, 0x87FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF, 0x07FFFFFF },
	{ 0xFFFFFFFF, 0xEFFFFFFF, 0xCFFFFFFF, 0x8FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF },
	{ 0xFFFFFFFF, 0xDFFFFFFF, 0x9FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF },
	{ 0xFFFFFFFF, 0xBFFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF },
	{ 0xFFFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF },
};

struct c_bf_write {
	c_bf_write(char* data, size_t size) : data(data), data_size(size & ~3), cur_bit(0) {
		this->data_bits = (size & ~3) << 3;
	}

	__forceinline void set_overflow_flag() {
		this->overflow = true;
	}

	__forceinline bool check_overflow(int bits) {
		if (this->cur_bit + bits > this->data_bits)
			set_overflow_flag();

		return this->overflow;
	}

	__forceinline void write_bit(bool value) {
		if (check_overflow(1))
			return;
		
		if (value)
			this->data[this->cur_bit >> 3] |= 1 << (this->cur_bit & 7);
		else
			this->data[this->cur_bit >> 3] &= ~(1 << (this->cur_bit & 7));

		this->cur_bit++;
	}

	__forceinline void write_bits(void* cur_data, int in_bits) {
		if (check_overflow(in_bits)) {
			this->cur_bit = this->data_bits;
			return;
		}

		auto in_data = reinterpret_cast<uint8_t*>(cur_data);
		int bits_left = in_bits;

		while ((reinterpret_cast<uintptr_t>(in_data) & 3) != 0 && bits_left >= 8) {
			write_ubit_long(*in_data, 8);
			++in_data;
			bits_left -= 8;
		}

		if (bits_left >= 32) {
			if ((this->cur_bit & 7) == 0) {
				int num_bytes = bits_left >> 3;
				int num_bits = num_bytes << 3;

				memcpy(this->data + (this->cur_bit >> 3), in_data, num_bytes);

				in_data += num_bytes;
				bits_left -= num_bits;
				this->cur_bit += num_bits;
			} else {
				const uint32_t bits_at_right = (this->cur_bit & 31);
				const uint32_t bits_at_left = 32 - bits_at_right;
				const int bits_changing = 32 + bits_at_left;
				uint32_t dword_idx = this->cur_bit >> 5;

				uint32_t out_dword = reinterpret_cast<uint32_t*>(this->data)[dword_idx];
				out_dword &= bit_write_mask[bits_at_right][32];

				while (bits_left >= bits_changing) {
					uint32_t current_data = *reinterpret_cast<uint32_t*>(in_data);
					in_data += sizeof(uint32_t);

					out_dword |= current_data << bits_at_right;
					reinterpret_cast<uint32_t*>(this->data)[dword_idx] = out_dword;

					++dword_idx;
					out_dword = current_data >> bits_at_left;

					bits_left -= 32;
					this->cur_bit += 32;
				}

				reinterpret_cast<uint32_t*>(this->data)[dword_idx] = out_dword;

				if (bits_left >= 32) {
					write_ubit_long(*reinterpret_cast<uint32_t*>(in_data), 32);
					in_data += sizeof(uint32_t);
					bits_left -= 32;
				}
			}
		}

		while (bits_left >= 8) {
			write_ubit_long(*in_data, 8);
			++in_data;
			bits_left -= 8;
		}

		if (bits_left)
			write_ubit_long(*in_data, bits_left);
	}

	__forceinline void write_sbit_long(int32_t cur_data, int num_bits) {
		if (cur_data > 0) {
			write_ubit_long(static_cast<uint32_t>(cur_data), num_bits - 1);
			write_bit(0);
			return;
		}

		write_ubit_long(static_cast<uint32_t>(0x80000000 + cur_data), num_bits - 1);
		write_bit(1);
	}

	__forceinline void write_ubit_long(uint32_t cur_data, int num_bits) {
		if (check_overflow(num_bits)) {
			this->cur_bit = this->data_bits;
			return;
		}

		int bits_left = num_bits;
		uint32_t dword_idx = this->cur_bit >> 5;
		uint32_t cur_bit_masked = this->cur_bit & 31;

		uint32_t dword = reinterpret_cast<uint32_t*>(this->data)[dword_idx];
		dword &= bit_write_mask[cur_bit_masked][bits_left];
		dword |= cur_data << cur_bit_masked;

		reinterpret_cast<uint32_t*>(this->data)[dword_idx] = dword;

		int bits_written = 32 - cur_bit_masked;
		if (bits_written < bits_left) {
			bits_left -= bits_written;
			cur_data >>= bits_written;

			dword = reinterpret_cast<uint32_t*>(this->data)[dword_idx + 1];
			dword &= bit_write_mask[0][bits_left];
			dword |= cur_data;

			reinterpret_cast<uint32_t*>(this->data)[dword_idx + 1] = dword;
		}

		this->cur_bit += num_bits;
	}

	__forceinline void write_float(float value) {
		write_bits(&value, sizeof(float) << 3);
	}

	__forceinline void write_short(int value) {
		if (value > 0) {
			write_ubit_long(static_cast<uint32_t>(value), 15);
			write_bit(0);
			return;
		}

		write_ubit_long(static_cast<uint32_t>(0x80000000 + value), 15);
		write_bit(1);
	}

	__forceinline size_t current_byte() const {
		return (cur_bit + 7) >> 3;
	}

private:
	char* data;
	size_t data_size;
	size_t data_bits;
	size_t cur_bit;
	bool overflow{ 0 };
	bool assert_on_overflow{ 1 };
};

class c_bit_buf {
public:
	char const* debug_name;
	bool overflow;
	int data_bits;
	size_t data_bytes;

	c_bit_buf() {
		overflow = false;
		debug_name = NULL;
		data_bits = -1;
		data_bytes = 0;
	}

	__forceinline void set_overflow_flag() {
		overflow = true;
	}

	__forceinline bool is_overflowed() const {
		return overflow;
	}
};

class c_bit_read : public c_bit_buf {
public:
	uint32_t in_buf_word;
	int bits_avail;
	uint32_t const* data_in;
	uint32_t const* buffer_end;
	uint32_t const* data;

	c_bit_read(const void* data, int num_bytes, int num_bits = -1) {
		this->data = this->data_in = reinterpret_cast<uint32_t const*>(data);
		this->data_bytes = num_bytes;

		if (num_bits == -1)
			this->data_bits = num_bytes << 3;
		else
			this->data_bits = num_bits;

		this->overflow = false;
		this->buffer_end = reinterpret_cast<uint32_t const*>(reinterpret_cast<uint8_t const*>(this->data) + num_bytes);
		
		if (this->data)
			this->seek(0);
	}

	__forceinline bool seek(int position) {
		bool success = true;

		if (position < 0 || position > this->data_bits) {
			this->set_overflow_flag();
			success = false;
			position = this->data_bits;
		}

		int head = this->data_bytes & 3;
		int byte_offs = position / 8;

		if ((this->data_bytes < 4) || (head && (byte_offs < head))) {
			auto partial = reinterpret_cast<uint8_t const*>(this->data);

			if (this->data) {
				this->in_buf_word = *(partial++);
				if (head > 1)
					this->in_buf_word |= (*partial++) << 8;
				if (head > 2)
					this->in_buf_word |= (*partial++) << 16;
			}

			this->data_in = reinterpret_cast<uint32_t const*>(partial);
			this->in_buf_word >>= (position & 31);
			this->bits_avail = (head << 3) - (position & 31);
		} else {
			int adj_position = position - (head << 3);
			
			this->data_in = reinterpret_cast<uint32_t const*>(reinterpret_cast<uint8_t const*>(this->data) + ((adj_position / 32) << 2) + head);
			
			if (this->data) {
				this->bits_avail = 32;
				grab_next_dword();
			} else {
				this->in_buf_word = 0;
				this->bits_avail = 1;
			}

			this->in_buf_word >>= (adj_position & 31);
			this->bits_avail = min(this->bits_avail, 32 - (adj_position & 31));
		}

		return success;
	}

	__forceinline int read_bit() {
		int ret = this->in_buf_word & 1;
		
		if (this->bits_avail-- == 1)
			this->fetch_next();
		else
			this->in_buf_word >>= 1;
		
		return ret;
	}

	__forceinline uint32_t read_ubit_long(int num_bits) {
		if (this->bits_avail >= num_bits) {
			const auto ret = this->in_buf_word;
			
			this->bits_avail -= num_bits;
			
			if (this->bits_avail)
				this->in_buf_word >>= num_bits;
			else
				this->fetch_next();
			
			return ret;
		}

		auto ret = this->in_buf_word;
		num_bits -= this->bits_avail;

		this->grab_next_dword(true);
		if (this->is_overflowed())
			return NULL;

		ret |= (this->in_buf_word & mask_table[num_bits]) << this->bits_avail;
		
		this->bits_avail = 32 - num_bits;
		this->in_buf_word >>= num_bits;
	
		return ret;
	}

	__forceinline int read_sbit_long(int num_bits) {
		auto ret = read_ubit_long(num_bits);
		return (ret << (32 - num_bits)) >> (32 - num_bits);
	}

	__forceinline float read_float() {
		uint32_t ret = read_ubit_long(sizeof(int32_t) << 3);
		if (!ret)
			return 0.f;

		return *((float*)&ret);
	}

	__forceinline void fetch_next() {
		this->bits_avail = 32;
		this->grab_next_dword(false);
	}

	__forceinline void grab_next_dword(bool overflow_immediately = false) {
		if (this->data_in == this->buffer_end) {
			this->bits_avail = 1;
			this->in_buf_word = 0;
			this->data_in++;
			
			if (overflow_immediately)
				this->set_overflow_flag();
		}
		else if (data_in <= buffer_end) {
			this->in_buf_word = *this->data_in;
			this->data_in++;
		} else {
			this->set_overflow_flag();
			this->in_buf_word = 0;
		}
	}
};