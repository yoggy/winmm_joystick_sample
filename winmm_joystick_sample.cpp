#include <SDKDDKVer.h>
#include <windows.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main(int argc, char* argv[])
{
	JOYINFOEX ji;
	MMRESULT rv;

	while (true) {
		// https://msdn.microsoft.com/ja-jp/library/cc410475.aspx
		rv = joyGetPosEx(JOYSTICKID1, &ji);

		//
		// joystickapi.h
		//
		// typedef struct joyinfoex_tag {
		//     DWORD dwSize;                /* size of structure */
		//     DWORD dwFlags;               /* flags to indicate what to return */
		//     DWORD dwXpos;                /* x position */
		//     DWORD dwYpos;                /* y position */
		//     DWORD dwZpos;                /* z position */
		//     DWORD dwRpos;                /* rudder/4th axis position */
		//     DWORD dwUpos;                /* 5th axis position */
		//     DWORD dwVpos;                /* 6th axis position */
		//     DWORD dwButtons;             /* button states */
		//     DWORD dwButtonNumber;        /* current button number pressed */
		//     DWORD dwPOV;                 /* point of view state */
		//     DWORD dwReserved1;           /* reserved for communication between winmm & driver */
		//     DWORD dwReserved2;           /* reserved for future expansion */
		// } JOYINFOEX, *PJOYINFOEX, NEAR *NPJOYINFOEX, FAR *LPJOYINFOEX;

		if (rv == JOYERR_NOERROR) {
			printf("dwButtons=%04x, dwPOV=%04x, dwXpos=%04x, dwYpos=%04x, dwZpos=%04x, dwRpos=%04x, ",
				ji.dwButtons,
				ji.dwPOV,
				ji.dwXpos,
				ji.dwYpos,
				ji.dwZpos,
				ji.dwRpos
				);
		}
		else if (rv == MMSYSERR_NODRIVER) {
			printf("error : rv=MMSYSERR_NODRIVER : �W���C�X�e�B�b�N�h���C�o�����݂��܂���B\n");
		}
		else if (rv == MMSYSERR_INVALPARAM) {
			printf("error : rv=MMSYSERR_INVALPARAM : �����ȃp�����[�^���n����܂���\n");
		}
		else if (rv == MMSYSERR_BADDEVICEID) {
			printf("error : rv=MMSYSERR_BADDEVICEID : �w�肳�ꂽ�W���C�X�e�B�b�N���ʎq�͖����ł�\n");
		}
		else if (rv == JOYERR_UNPLUGGED) {
			printf("error : rv=JOYERR_UNPLUGGED : �w�肳�ꂽ�W���C�X�e�B�b�N�̓V�X�e���ɐڑ�����Ă��܂���\n");
		}

		::Sleep(500);
	}

	return 0;
}

